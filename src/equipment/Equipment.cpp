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
    if (type_ == EquipmentType::TYPE_CELL) {
        TxPower_ = 40;
        bodyLoss_ = 0;
        noiseFigure_ = 3;
        additionalGain_ = 18;
        additionalLoss_ = 3;
    } else if (type_ == EquipmentType::TYPE_UE) {
        TxPower_ = 23;
        bodyLoss_ = 0;
        noiseFigure_ = 7;
        additionalGain_ = 0;
        additionalLoss_ = 0;
    }
}

void Equipment::sync120TimeSlot(int &timeSlot)
{
    localSystem120TimeSlot_ = timeSlot;
}

int Equipment::getLocalSystem120TimeSlot()
{
    return localSystem120TimeSlot_;
}

// ----- [ COUNTERS ] --------------------------------------------------------------------------------------------------

void Equipment::setCountWindowSize(int windSize)
{
    cWindowSize_ = windSize;
}

void Equipment::addCountDataTransmitted(int bytes)
{
    cDataTransmitted_ += bytes;
}

void Equipment::calcCountDataTransmittedOverWindow()
{

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
