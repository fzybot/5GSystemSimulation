#pragma once

#include <math.h>
#include <QVector>
#include <QDebug>
#include <QGraphicsItem>

#include "src/commonParameters.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/core/CartesianCoordinates.h"

class Bearer;

class Equipment
{
public:
    enum class EquipmentState
    {
      STATE_DETACHED,
      STATE_ACTIVE,
      STATE_IDLE
    };

    enum class EquipmentType
    {
      TYPE_GNODEB,
      TYPE_CELL,
      TYPE_UE
    };

protected:
    int id_;

    double lastTime_;

    Equipment::EquipmentState state_;
    Equipment::EquipmentType type_;

    Mobility *mobility_;

    QVector<Bearer*> *bearerContainer_;

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

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setEquipmentID(int id);
    int getEquipmentID();

    void setEquipmentType(EquipmentType type);
    EquipmentType getEquipmentType() const;

    void setEquipmentState(EquipmentState state);
    EquipmentState getEquipmentState() const;

    void setMobilityModel(Mobility *model);
    Mobility* getMobilityModel(void);

    void createDefaultBearer(int id);
    void addBearer(Bearer *bearer);
    QVector<Bearer*> *getBearerContainer();

    void setLinkBudgetParameters();

    // ----- [ PHYSICAL METHODS ] ------------------------------------------------------------------------------------------
    void calculateThermalNoise();

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
    void print();

};
