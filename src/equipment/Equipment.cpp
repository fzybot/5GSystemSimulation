#include "Equipment.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>

#include "src/debug.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/phy/propagationModels.h"
#include "src/equipment/Cell.h"
#include "src/equipment/UserEquipment.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"

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

void Equipment::setPropagationModel(PropagationModel model)
{
    propagationModel_ = model;
}

Equipment::PropagationModel &Equipment::getPropagationModel()
{
    return propagationModel_;
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

void Equipment::setLinkBudgetParameters()
{
    qDebug() << "Equipment::setLinkBudgetParameters()";
    if (type_ == EquipmentType::TYPE_CELL) {
        TxPower_ = 43;
        bodyLoss_ = 0;
        noiseFigure_ = 3;
        additionalGain_ = 18;
        additionalLoss_ = 3;
        EIRP_ = TxPower_ - bodyLoss_ - additionalLoss_ + additionalGain_;
        qDebug() << "Equipment::setLinkBudgetParameters()::EIRP --> " << EIRP_;
    }
    else if (type_ == EquipmentType::TYPE_UE)
    {
        TxPower_ = 23;
        bodyLoss_ = 0;
        noiseFigure_ = 7;
        additionalGain_ = 0;
        additionalLoss_ = 0;
        EIRP_ = TxPower_ - bodyLoss_ - additionalLoss_ + additionalGain_;
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

double Equipment::calculatePathLosToCell(Cell *targetCell, double distance)
{
    double bandwidth = getPhyEntity()->getBandwidthContainer()[0][0]->getBandwidth();
    double heightBs = targetCell->getMobilityModel()->getPosition()->getCoordinateZ();
    double heightUe = getMobilityModel()->getPosition()->getCoordinateZ();
    int centerFrequency = targetCell->getPhyEntity()->getBandwidthContainer()[0][0]->getCarrierFreq();

    return UMi_LOS(distance, 1, heightBs, heightUe, centerFrequency/1000, 0, 0, 0);
}

double Equipment::calculatePathLosToUserEquipment(UserEquipment *targetUser, double distance)
{
    double heightUe = getMobilityModel()->getPosition()->getCoordinateZ();
    double heightUeTarget = targetUser->getMobilityModel()->getPosition()->getCoordinateZ();
    double centerFrequency = getPhyEntity()->getBandwidthContainer()[0][0]->getCarrierFreq();
    double bandwidth = getPhyEntity()->getBandwidthContainer()[0][0]->getBandwidth();

    return UMi_LOS(distance, 1, heightUeTarget, heightUe, centerFrequency/1000, 0, 0, 0);
}

double Equipment::calculateRssiFromUserEquipment(UserEquipment *targetUser, double pathLos)
{
    return targetUser->getEirp() - pathLos - getNoiseFigure() - 20;
}

double Equipment::calculateRssiFromCell(Cell *targetCell, double pathLos)
{
    return targetCell->getEirp() - pathLos - getNoiseFigure() - 20;
}

double Equipment::calculateRsrpFromRssi(double rssi)
{
    double bandwidth = getPhyEntity()->getBandwidthContainer()[0][0]->getBandwidth();
    int scs = getPhyEntity()->getBandwidthContainer()[0][0]->getSCS();
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

// ----- [ COUNTERS ] --------------------------------------------------------------------------------------------------


void Equipment::addCountDataTransmitted(int bits)
{
    cDataTransmitted_ += bits;
    cDataTransmittedContainer_.push_back(bits);
}

QVector<int> &Equipment::getDataTransmitted()
{
    return cDataTransmittedContainer_;
}

void Equipment::addCountTbTransmitted(int bits)
{
    cTbTransmittedContainer_.push_back(bits);
}

QVector<int> &Equipment::getTbTransmitted()
{
    return cTbTransmittedContainer_;
}

QVector<QVector<int>> &Equipment::getAllData()
{
    cAllDataContainer_.push_back(cDataTransmittedContainer_);
    cAllDataContainer_.push_back(cTbTransmittedContainer_);
    
    return cAllDataContainer_;
}

void Equipment::addCountPrbUtilized(int prb)
{
    cPrbUtilizedContainer_.push_back(prb);
}

QVector<int> &Equipment::getPrbUtilized()
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
        throughput += cDataTransmittedContainer_[i];
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


// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
void Equipment::print()
{

}
