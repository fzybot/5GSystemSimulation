#include "Equipment.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>

#include "src/debug.h"
#include "src/protocols/bearers/RadioBearer.h"

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

int Equipment::getEquipmentId()
{
    return id_;
}

Equipment::EquipmentType Equipment::getEquipmentType() const
{
    return type_;
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
