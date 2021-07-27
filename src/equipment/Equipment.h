#pragma once

#include <math.h>
#include <QVector>
#include <QDebug>
#include <QGraphicsItem>

#include "src/commonParameters.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/core/CartesianCoordinates.h"


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
    int ID_;

    double lastTime_;

    // Cartesian coordinates (center coordinates)
    CartesianCoordinates* position_;

    EquipmentState state_;
    EquipmentType type_;

    Mobility *mobility_;

    // TODO: Add physical layer
    // TODO: Add protocol stack

    // Link budget parameters
    float TxPower_;
    float bodyLoss_;
    float EIRP_;
    float noiseFigure_;
    float additionalGain_ = 0;



};
