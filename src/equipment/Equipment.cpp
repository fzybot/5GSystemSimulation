#include "Equipment.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>
#include <QPair>

#include "src/debug.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/phy/Channel/propagationModels.h"
#include "src/protocols/phy/Channel/PropagationLossModel.h"
#include "src/equipment/Cell.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/antenna/AntennaArray.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Bandwidth.h"


// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Equipment::Equipment() 
{
    mobility_ = nullptr;
}

// Equipment::Equipment(int id, EquipmentType type, EquipmentState state)
// {
//     setEquipmentID(id);
//     setEquipmentType(type);
//     setEquipmentState(state);
// }

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void Equipment::setEquipmentId(int id)
{
    debug("Equipment: setting equipment id.");
    id_ = id;
    debug("Equipment: id = ", id_);
}

int Equipment::getEquipmentId()
{
    return id_;
}

void Equipment::setEquipmentState(EquipmentState state)
{
    state_ = state;
}

Equipment::EquipmentState Equipment::getEquipmentState() const
{
    return state_;
}

void Equipment::setEquipmentType(EquipmentType type)
{
    type_ = type;
}

Equipment::EquipmentType Equipment::getEquipmentType() const
{
    return type_;
}

void Equipment::setPropagationModel(PropagationLossModel *model)
{
    _propagationModel = model;
}

PropagationLossModel *Equipment::getPropagationModel()
{
    return _propagationModel;
}

void Equipment::setMobilityModel(Mobility* model)
{
    mobility_ = model;
}

Mobility* Equipment::getMobilityModel(void)
{
    return mobility_;
}

void Equipment::createDefaultBearer(int id)
{
    RadioBearer *bearer = new RadioBearer();
    bearer->createDefaultBearer(id);
    bearerContainer_->push_back(bearer);
}

void Equipment::createBearer(RadioBearer::RadioBearerType type, int id, int QoSProfile)
{
    RadioBearer *bearer = new RadioBearer();
    bearer->createRadioBearer(type, id, QoSProfile);
    bearerContainer_->push_back(bearer);
}

QVector<RadioBearer*> *Equipment::getBearerContainer()
{
    return bearerContainer_;
}

void Equipment::createPhyEntity()
{
    phyEntity_ = new Physical();
}

void Equipment::setPhyEntity(Physical *phy)
{
    phyEntity_ = phy;
}

Physical *Equipment::getPhyEntity()
{
    return phyEntity_;
}

void Equipment::addAntennaArray(AntennaArray::AntennaType type, int sizeX, int sizeY, 
                    float azimuth, float elevation, float beamWidth, float sectorWidth)
{
    getPhyEntity()->addAntennaArray(type, sizeX, sizeY, azimuth, elevation, beamWidth, sectorWidth);
}

AntennaArray *Equipment::getAntennaArray()
{
    getPhyEntity()->getAntennaArray();
}

void Equipment::setLinkBudgetParameters()
{
    qDebug() << "Equipment::setLinkBudgetParameters()";
    if (type_ == EquipmentType::TYPE_CELL) 
    {
        TxPower_ = 43;
        bodyLoss_ = 0;
        noiseFigure_ = 3;
        additionalGain_ = 18;
        additionalLoss_ = 3;
        EIRP_ = TxPower_ - bodyLoss_ - additionalLoss_ + additionalGain_;
        qDebug() << "   " <<"Equipment::setLinkBudgetParameters()::EIRP --> " << EIRP_;
    }
    else if (type_ == EquipmentType::TYPE_UE)
    {
        TxPower_ = 23;
        bodyLoss_ = 0;
        noiseFigure_ = 7;
        additionalGain_ = 0;
        additionalLoss_ = 0;
        EIRP_ = TxPower_ - bodyLoss_ - additionalLoss_ + additionalGain_;
        qDebug() << "   " << "Equipment::setLinkBudgetParameters()::EIRP --> " << EIRP_;
    }
}

float Equipment::getEirp()
{
    return EIRP_;
}

float Equipment::getNoiseFigure()
{
    return noiseFigure_;
}

double Equipment::calculateDistanceToCell(Cell *targetCell)
{
    return getMobilityModel()->getPosition()->calculateDistance2D(targetCell->getMobilityModel()->getPosition());
}

double Equipment::calculateDistanceToUserEquipment(UserEquipment *targetUser)
{
    return getMobilityModel()->getPosition()->calculateDistance2D(targetUser->getMobilityModel()->getPosition());
}

double Equipment::calculateAngeToUserEquipment(UserEquipment *targetUser)
{
    return getMobilityModel()->getPosition()->calculateAngleToRemote(this->getMobilityModel()->getPosition(),
                                                                    targetUser->getMobilityModel()->getPosition());
}

double Equipment::calculateAngeToUserEquipmentRad(UserEquipment *targetUser)
{
    return getMobilityModel()->getPosition()->calculateAngleToRemoteRad(this->getMobilityModel()->getPosition(),
                                                                    targetUser->getMobilityModel()->getPosition());
}

double Equipment::calculatePathLosToCell(Cell *targetCell, double distance)
{
    int carrAggIndex = 0;
    int mimoIndex = 0;
    double bandwidth = getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex]->getBandwidth();
    double heightBs = targetCell->getMobilityModel()->getPosition()->getCoordinateZ();
    double heightUe = getMobilityModel()->getPosition()->getCoordinateZ();
    int centerFrequency = targetCell->getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex]->getCarrierFreq();

    return getPropagationModel()->calculateLosses(distance, 1, heightBs, heightUe, centerFrequency/1000, 0, 0, 0);
}

double Equipment::calculatePathLosToUserEquipment(UserEquipment *targetUser, double distance)
{
    // TODO: add frequency filter
    int carrAggIndex = 0;
    int mimoIndex = 0;
    double heightUe = getMobilityModel()->getPosition()->getCoordinateZ();
    double heightUeTarget = targetUser->getMobilityModel()->getPosition()->getCoordinateZ();
    double centerFrequency = getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex]->getCarrierFreq();
    double bandwidth = getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex]->getBandwidth();

    return getPropagationModel()->calculateLosses(distance, 1, heightUeTarget, heightUe, centerFrequency/1000, 0, 0, 0);
}

double Equipment::calculateRssiFromUserEquipment(UserEquipment *targetUser, double distance)
{
    double pathLoss = calculatePathLosToUserEquipment(targetUser, distance);
    return targetUser->getEirp() - pathLoss - getNoiseFigure();
}

double Equipment::calculateRssiFromCell(Cell *targetCell, double distance)
{
    double pathLoss = calculatePathLosToCell(targetCell, distance);
    return targetCell->getEirp() - pathLoss - getNoiseFigure();
}

double Equipment::calculateRsrpFromRssi(Bandwidth *BW, double rssi)
{
    double bandwidth = BW->getBandwidth();
    int scs = BW->getSCS();
    double rsrp = rssi - 10*log10(bandwidth*1000/scs);
    return rsrp;
}

void Equipment::sync120TimeSlot(int &timeSlot)
{
    localSystem120TimeSlot_ = timeSlot;
}

int Equipment::getLocalSystem120TimeSlot()
{
    return localSystem120TimeSlot_;
}


void Equipment::syncOwnTimeSlot(int timeSlot)
{
    localOwnTimeSlot_ = timeSlot;
}

int Equipment::getLocalOwnTimeSlot()
{
    return localOwnTimeSlot_;
}

void Equipment::setRsrpPerBandidth(double rsrp, int bwIndex)
{
    int carrAggIndex = 0;
    getPhyEntity()->getBandwidthContainer()[carrAggIndex][bwIndex]->setRsrp(rsrp);
}

void Equipment::setRsrqPerBandidth(double rsrq, int bwIndex)
{
    int carrAggIndex = 0;
    getPhyEntity()->getBandwidthContainer()[carrAggIndex][bwIndex]->setRsrq(rsrq);
}

void Equipment::setSinrPerBandidth(double sinr, int bwIndex)
{
    int carrAggIndex = 0;
    getPhyEntity()->getBandwidthContainer()[carrAggIndex][bwIndex]->setSinr(sinr);
}

double Equipment::getRsrqPerBandidth(int bwIndex)
{
    int carrAggIndex = 0;
    return getPhyEntity()->getBandwidthContainer()[carrAggIndex][bwIndex]->getRsrq();
}

double Equipment::getRsrpPerBandidth(int bwIndex)
{
    int carrAggIndex = 0;
    return getPhyEntity()->getBandwidthContainer()[carrAggIndex][bwIndex]->getRsrp();
}

double Equipment::getSinrPerBandidth(int bwIndex)
{
    int carrAggIndex = 0;
    return getPhyEntity()->getBandwidthContainer()[carrAggIndex][bwIndex]->getSinr();
}


// ----- [ COUNTERS ] --------------------------------------------------------------------------------------------------


void Equipment::addCountDataTransmitted(int slot, int bits)
{
    QPair<int, int> local_;
    local_.first = slot;
    local_.second = bits;
    cDataTransmitted_ += bits;
    cDataTransmittedContainer_.push_back(local_);
}

QVector<QPair<int, int>> &Equipment::getDataTransmitted()
{
    return cDataTransmittedContainer_;
}

void Equipment::showDataTransmitted()
{
        qDebug() << "Equipment::showDataTransmitted():: BITS" << cDataTransmitted_;
}

void Equipment::addCountTbTransmitted(int slot, int bits)
{
    QPair<int, int> local_;
    local_.first = slot;
    local_.second = bits;
    cTbTransmittedContainer_.push_back(local_);
}

QVector<QPair<int, int>> &Equipment::getTbTransmitted()
{
    return cTbTransmittedContainer_;
}

QVector<QVector<QPair<int, int>>> &Equipment::getAllData()
{
    cAllDataContainer_.push_back(cDataTransmittedContainer_);
    cAllDataContainer_.push_back(cTbTransmittedContainer_);
    cAllDataContainer_.push_back(cPrbUtilizedContainer_);

    return cAllDataContainer_;
}

void Equipment::addCountPrbUtilized(int slot, int prb)
{
    QPair<int, int> local_;
    local_.first = slot;
    local_.second = prb;
    cPrbUtilizedContainer_.push_back(local_);
}

QVector<QPair<int, int>> &Equipment::getPrbUtilized()
{
    return cPrbUtilizedContainer_;
}

int Equipment::calcCountDataTransmittedOverWindow(int windowSize)
{
    int throughput = 0;
    int length = cDataTransmittedContainer_.length();
    if(length < windowSize)
        length = 0;
    for (int i = length - 1; i >= length - windowSize; i--) {
        throughput += cDataTransmittedContainer_[i].first;
    }
    return throughput;
}

void Equipment::addCountSuccPacketTransmitted()
{
    cSuccPacketTransmitted_++;
}

// ----- [ PHYSICAL METHODS ] ------------------------------------------------------------------------------------------
void Equipment::calculateThermalNoise()
{
    //this->thermalNoise = -174 + 10 * log10(this->bandwidth * 1000000);
}



// ----- [ Visualizing ] -----------------------------------------------------------------------------------------------

void Equipment::visualizeCounters()
{

}


// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
void Equipment::print()
{

}
