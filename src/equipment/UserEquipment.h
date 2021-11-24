#pragma once


#include "src/equipment/Equipment.h"
#include "src/protocols/Packet.h"
#include "src/protocols/bearers/QoS/QoSProfile.h"
#include <QVector>

class gNodeB;
class Cell;

class UserEquipment : public Equipment
{

protected:
    gNodeB              *targetGNodeB_;
    Cell                *targetCell_;
    QVector<Packet*>    packetsInBuffer_;
    QVector<Packet*>    packetsPerCurrentSlot_;
    QVector<Packet*>    packetsHarq_;
    int                 gPacketId_ = 1000;

    int slotToCampOnCell_ = 0;

    // TODO: for this part of code it is needed to do a lot of classes for all simplified objects
    double      sinr_;
    bool        BSR_ = true;
    bool        measurementGAP_ = false;
    bool        DRX_ = false;
    int         bufferSize_ = 0;

    // Measurements for target Cell
    double targetCellRsrp;
    double targetCellRsrq;
    double targetCellRssi;


public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    UserEquipment();
    UserEquipment(int id, 
                  double posX, double posY, double posZ, 
                  Cell *cell, gNodeB *targetGNodeB, 
                  Mobility::Model model);

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setTargetCell(Cell *cell);
    Cell *getTargetCell();

    void setTargetGNodeB(gNodeB *gNb);
    gNodeB *getTargetGNodeB();

    void addToBuffer(int size);
    void decreaseBuffer(int decSize);
    int getBufferSize();

    void generatePackets(int number, int currentSlot, RadioBearer *bearer);
    QVector<Packet*> &getPacketsContainer();
    QVector<Packet*> &getPacketsContainerCurrentSlot(int slot);
    void generatePacketsPerBearer(int slot);
    void deletePackets(QVector<Packet*> &packetsToDelete);
    void deletePacket(Packet *packetToDelete);
    void showPacketsInBuffer();
    void updatePacketTransmitSlot(int slot);

    void setSlotToCamp(int slot);
    int getSlotToCamp();

    void setBSR(bool bsr);
    bool getBSR();
    void setMeasurementGap(bool gap);
    bool getMeasurementGap();
    void setDRX(bool drx);
    bool getDRX();
    void setSINR(double sinr);
    double getSINR();

    // ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
    void calculateEIRP();

    //void addNeighbourCell(BaseStation cell);
};
