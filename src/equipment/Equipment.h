#pragma once

#include <math.h>
#include <QVector>
#include <QDebug>
#include <QGraphicsItem>

#include "src/commonParameters.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/core/CartesianCoordinates.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/phy/Channel/Bandwidth.h"

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
        UMa_NLOS,
        COST231_Hata,
    };

public:
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
    float TxPower_ = 0;
    float bodyLoss_ = 0;
    float EIRP_ = 0;
    float noiseFigure_ = 0;
    float additionalGain_ = 0;
    float additionalLoss_ = 0;

    // Bandwidth info
    // Should be info about (signal power | noise | interference | SINR).
    QVector<QVector<double>> iSubcarrierPowerUsage_; 

    // COUNTERS
    // Throughput
    int cDataTransmitted_ = 0;           // in [bits]
    int cDataTransmittedOverWindow_ = 0; // in [bits]
    QVector<QPair<int, int>> cDataTransmittedContainer_; // per Slot
    QVector<QPair<int, int>> cTbTransmittedContainer_; // per Slot
    QVector<QPair<int, int>> cPrbUtilizedContainer_; // per Slot

    QVector<QVector<QPair<int, int>>> cAllDataContainer_;

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

    void        createPhyEntity();
    void        setPhyEntity(Physical *phy);
    Physical    *getPhyEntity();

    void    setLinkBudgetParameters();
    float   getEirp();
    float   getNoiseFigure();

    void setRsrpPerBandidth(double rsrp, int bwIndex);
    void setRsrqPerBandidth(double rsrq, int bwIndex);
    void setSinrPerBandidth(double sinr, int bwIndex);

    double getRsrqPerBandidth(int bwIndex);
    double getRsrpPerBandidth(int bwIndex);
    double getSinrPerBandidth(int bwIndex);

    double calculateDistanceToCell(Cell *targetCell);
    double calculateDistanceToUserEquipment(UserEquipment *targetUser);
    double calculatePathLosToCell(Cell *targetCell, double distance);
    double calculatePathLosToUserEquipment(UserEquipment *targetUser, double distance);
    double calculateRssiFromUserEquipment(UserEquipment *targetUser, double distance);
    double calculateRssiFromCell(Cell *targetCell, double distance);
    double calculateRsrpFromRssi(Bandwidth *BW, double rssi);

    void sync120TimeSlot(int &timeSlot);
    int getLocalSystem120TimeSlot();
    void syncOwnTimeSlot(int timeSlot);
    int getLocalOwnTimeSlot();

    // ----- [ PHYSICAL METHODS ] ------------------------------------------------------------------------------------------
    void calculateThermalNoise();

    // ----- [ COUNTERS ] --------------------------------------------------------------------------------------------------
    void addCountDataTransmitted(int slot, int bits);
    QVector<QPair<int, int>> &getDataTransmitted();
    int calcCountDataTransmittedOverWindow(int windowSize);
    void showDataTransmitted();

    void addCountTbTransmitted(int slot, int bits);
    QVector<QPair<int, int>> &getTbTransmitted();

    QVector<QVector<QPair<int, int>>> &getAllData();

    void addCountPrbUtilized(int slot, int prb);
    QVector<QPair<int, int>> &getPrbUtilized();

    void addCountSuccPacketTransmitted();

    void visualizeCounters();

    // ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
    void print();

};
