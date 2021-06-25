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
    m_ID = id;
}

void Equipment::setEquipmentState(EquipmentState state)
{
    m_state = state;
}

void Equipment::setEquipmentType(EquipmentType type)
{
    m_type = type;
}

void Equipment::setCartesianPosition(double x, double y, double z)
{
    m_posX = x;
    m_posY = y;
    m_posZ = z;
}


//**************************************************************
// Physical effects methods
//**************************************************************
void Equipment::calculateThermalNoise()
{
    //this->thermalNoise = -174 + 10 * log10(this->bandwidth * 1000000);
}


