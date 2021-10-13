#pragma once

#include <QVector>
#include <QBitArray>
#include "src/protocols/Protocol.h"
#include "src/protocols/mac_layer/TransportBlock.h"
#include "src/protocols/Packet.h"
#include "src/equipment/Cell.h"

class AMCEntity;
class HARQEntity;
class RlcPacket;

class MacEntity
{
protected:
    // Connected Entities
    Cell *device_;
    AMCEntity *amcEntity_;
    HARQEntity *harqEntity_;

    // Data in buffer
    QVector<TransportBlock> transportBlockContainer_;

    // PHY configuration
    QVector< QVector< QBitArray > > *resourceElementMatrix; // per 1 slot
    int CORESETS_size_;
    int BWP_size_;

    // KPIs
    int dataTransmitted; // [bits]
    int macThroughput;

public:
    MacEntity();
    virtual ~MacEntity() {};

    void setDevice(Cell *e);
    Cell *getDevice();

    void createAMCEntity();
    void setAMCEntity(AMCEntity *amc);
    AMCEntity *getAMCEntity (void);
    void delAMCEntity();

    void configMacEntity();

    //TODO: Deal with the scheduler
    //void createShcedulerEntity();

    void packetsToTransportBlockContainer(QVector<Packet> &packetContainer);
    QVector<TransportBlock> &getTransportBlockContainer();

    TransportBlock* packetToTBS(Packet &packet);
    TransportBlock* rlcToTBS(RlcPacket &packet);
};
