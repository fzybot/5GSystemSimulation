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

private:
    int ID_;

    double lastTime_;

    Equipment::EquipmentState state_;
    Equipment::EquipmentType type_;

    Mobility *mobility_;

    // TODO: Add physical layer
    // TODO: Add protocol stack

    // Link budget parameters
    float TxPower_;
    float bodyLoss_;
    float EIRP_;
    float noiseFigure_;
    float additionalGain_ = 0;
    float additionalLoss_ = 0;

public:
// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
    Equipment();
    Equipment(int id, EquipmentType type, EquipmentState state);

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setID(int id);
    int getID();

    void setEquipmentType(EquipmentType type);
    EquipmentType getEquipmentType() const;

    void setEquipmentState(EquipmentState state);
    EquipmentState getEquipmentState() const;

    void setMobilityModel(Mobility *movdel);
    Mobility* getMobilityModel(void);

// ----- [ PHYSICAL METHODS ] ------------------------------------------------------------------------------------------
    void calculateThermalNoise();
};
