#include "Equipment.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>


Equipment::Equipment() {

}

Equipment::Equipment(int id, EquipmentType type, EquipmentState state)
{
    setID(id);
    setEquipmentType(type);
    setEquipmentState(state);
}

void Equipment::setID(int id)
{
    ID_ = id;
}

void Equipment::setEquipmentState(EquipmentState state)
{
    state_ = state;
}

void Equipment::setEquipmentType(EquipmentType type)
{
    type_ = type;
}


//**************************************************************
// Physical effects methods
//**************************************************************
void Equipment::calculateThermalNoise()
{
    //this->thermalNoise = -174 + 10 * log10(this->bandwidth * 1000000);
}


