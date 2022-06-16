#pragma once

#include "src/protocols/mac_layer/scheduler/Scheduler.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Physical.h"

class AMCEntity;
class HARQEntity;
class RlcPacket;

class CellMacEntity
{
private:

    // Connected Entities
    AMCEntity   *amcEntity_;
    HARQEntity  *harqEntity_;
    Cell *_cell;
    Scheduler *_scheduler;

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
    CellMacEntity(Cell *cell);

    void createScheduler(Scheduler::SchedulingAlgorithm algo);
    Scheduler *getScheduler();
    void schedule();

    void assignCell(Cell *cell);
    Cell *getCell();

    void createAMCEntity();
    void setAMCEntity(AMCEntity *amc);
    AMCEntity *getAMCEntity (void);
    void delAMCEntity();

    void configMacEntity();

    //TODO: Deal with the scheduler
    //void createShcedulerEntity();

    int calculateTransportBlockSize(int packetSize);

    void packetsToTransportBlockContainer(QVector<Packet> &packetContainer);
    QVector<TransportBlock> &getTransportBlockContainer();

    TransportBlock* packetToTBS(Packet &packet);
    TransportBlock* rlcToTBS(RlcPacket &packet);
};
