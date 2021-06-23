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
    /*
     * Coordinates & Geometry for spherical basis
     * According to 3GPP TS38.901:
     *  latitude is 'y' axis
     *  lontitude is 'x' axis
     *  altitude is  'z' axis (height above the sea)
     *
     *  angles:
     *      lonAngle - 'fi'
     *      latAngle - '0'
     *  variables: pixelX, pixelY, pixelZ is used to draw an image
     *  There are functions to transform pixel into latlon and inverse
     */

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

private:
    int ID;

    double altitude = 0;
    double longtitude;
    double latitude;

    double lonAngle = 0;
    double latAngle = 0;
    double altAngle = 0;

    int pixelX;
    int pixelY;
    int pixelZ;

    EquipmentState m_state;
    EquipmentType m_type;

    Mobility *m_mobility;

    // TODO: Add physical layer
    // TODO: Add protocol stack
    // TODO: Add positioning. For now alt lon lat is working


public:
    Equipment();

    void calculateThermalNoise();
};
