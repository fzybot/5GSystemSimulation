#include "Equipment.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>

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

void Equipment::setEquipmentID(int id)
{
    id_ = id;
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

int Equipment::getEquipmentID()
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

// ----- [ PHYSICAL METHODS ] ------------------------------------------------------------------------------------------
void Equipment::calculateThermalNoise()
{
    //this->thermalNoise = -174 + 10 * log10(this->bandwidth * 1000000);
}


// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
void Equipment::print()
{
    // if (type_ == EquipmentType::TYPE_GNODEB) {
    //     qDebug() << "TYPE_GNODEB";
    // }
    // else if (type_ == EquipmentType::TYPE_CELL) {
    //     qDebug() << "TYPE_CELL";
    // }
    // else if (type_ == EquipmentType::TYPE_UE) {
    //     qDebug() << "TYPE_UE";
    // }
    qDebug() << type_;
    qDebug() << "Identity: " << id_;
    mobility_->getPosition()->print();
    
}
