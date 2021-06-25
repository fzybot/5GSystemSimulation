#pragma once

#include <math.h>
#include <QVector>
#include <QDebug>
#include <QGraphicsItem>
#include "src/commonParameters.h"
#include "src/mobility/Mobility.h"

class Equipment
{
public:
    enum EquipmentState
    {
      STATE_DETACHED,
      STATE_ACTIVE,
      STATE_IDLE
    };

    enum EquipmentType
    {
      TYPE_GNODEB,
      TYPE_UE,
    };

public:
    Equipment();
    Equipment(int id, EquipmentType type, EquipmentState state);

    void setID(int id);
    int getID();

    void setEquipmentType(EquipmentType type);
    EquipmentType getEquipmentType();

    void setEquipmentState(EquipmentState state);
    EquipmentState getEquipmentState();

    void setCartesianPosition(double x, double y, double z);

    void makeStep(double time, double angleX, double angleY,double angleZ);

    void calculateThermalNoise();

private:
    int m_ID;

    double m_lastTime;

    // Geographical coordinates
    double m_altitude = 0;
    double m_longtitude;
    double m_latitude;

    double m_lonAngle = 0;
    double m_latAngle = 0;
    double m_altAngle = 0;

    // Image coordinates
    int m_pixelX;
    int m_pixelY;
    int m_pixelZ;

    // Cartesian coordinates
    double m_posX;
    double m_posY;
    double m_posZ;

    double m_angleX;
    double m_angleY;
    double m_angleZ;

    EquipmentState m_state;
    EquipmentType m_type;

    Mobility *m_mobility;

    // TODO: Add physical layer
    // TODO: Add protocol stack
    // TODO: Add positioning. For now alt lon lat is working

};
