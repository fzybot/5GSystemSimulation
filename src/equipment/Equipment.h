#pragma once

#include <math.h>
#include <QVector>
#include <QDebug>
#include <QGraphicsItem>

#include "src/commonParameters.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/core/CartesianCoordinates.h"
#include "src/protocols/bearers/RadioBearer.h"

class Cell;
class UserEquipment;
class Physical;

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

    enum class PropagationModel
    {
        UMi_LOS,
        UMi_NLOS,
        UMa_LOS,
        UMaNLOS
    };

protected:
    int     id_;
    int     localSystem120TimeSlot_ = 0;
    int     localOwnTimeSlot_ = 0;
    double  lastTime_;

    Equipment::EquipmentState   state_;
    Equipment::EquipmentType    type_;
    Equipment::PropagationModel propagationModel_;

    Mobility                *mobility_;
    QVector<RadioBearer*>   *bearerContainer_;

    Physical        *phyEntity_;

    // TODO: Add physical layer
    // TODO: Add protocol stack

    // Link budget parameters
    float TxPower_;
    float bodyLoss_;
    float EIRP_;
    float noiseFigure_;
    float additionalGain_ = 0;
    float additionalLoss_ = 0;

    // COUNTERS
    // Throughput
    int cDataTransmitted_ = 0;           // in [bits]
    int cDataTransmittedOverWindow_ = 0; // in [bits]
    QVector<int> cDataTransmittedContainer_; // per Slot
    QVector<int> cTbTransmittedContainer_; // per Slot
    QVector<int> cPrbUtilizedContainer_; // per Slot

    QVector<QVector<int>> cAllDataContainer_;

    // Delays
    int cSuccPacketTransmitted_ = 0;
    int cNumberOfPacketRetr_ = 0;
    int cAveragePacketDelay_;
    // Losses

public:
// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
    Equipment();

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setEquipmentId(int id);
    int getEquipmentId();

    void setEquipmentType(EquipmentType type);
    EquipmentType getEquipmentType() const;

    void setEquipmentState(EquipmentState state);
    EquipmentState getEquipmentState() const;

    void setPropagationModel(PropagationModel model);
    PropagationModel &getPropagationModel();

    void setMobilityModel(Mobility *model);
    Mobility* getMobilityModel(void);

    void createDefaultBearer(int id);
    void createBearer(RadioBearer::RadioBearerType type, int id, int QoSProfile);
    QVector<RadioBearer*> *getBearerContainer();

    void createPhyEntity();
    void setPhyEntity(Physical *phy);
    Physical *getPhyEntity();

    void setLinkBudgetParameters();
    float getEirp();
    float getNoiseFigure();

    double calculateDistanceToCell(Cell *targetCell);
    double calculateDistanceToUserEquipment(UserEquipment *targetUser);
    double calculatePathLosToCell(Cell *targetCell, double distance);
    double calculatePathLosToUserEquipment(UserEquipment *targetUser, double distance);
    double calculateRssiFromUserEquipment(UserEquipment *targetUser, double pathLos);
    double calculateRssiFromCell(Cell *targetCell, double pathLos);
    double calculateRsrpFromRssi(double rssi);

    void sync120TimeSlot(int &timeSlot);
    int getLocalSystem120TimeSlot();
    void syncOwnTimeSlot(int timeSlot);
    int getLocalOwnTimeSlot();

    // ----- [ PHYSICAL METHODS ] ------------------------------------------------------------------------------------------
    void calculateThermalNoise();

// ----- [ COUNTERS ] --------------------------------------------------------------------------------------------------
    void addCountDataTransmitted(int bits);
    QVector<int> &getDataTransmitted();
    int calcCountDataTransmittedOverWindow(int windowSize);

    void addCountTbTransmitted(int bits);
    QVector<int> &getTbTransmitted();

    QVector<QVector<int>> &getAllData();

    void addCountPrbUtilized(int prb);
    QVector<int> &getPrbUtilized();

    void addCountSuccPacketTransmitted();

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
    void print();

};
