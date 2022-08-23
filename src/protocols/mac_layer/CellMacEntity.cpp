
#include "CellMacEntity.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"
#include "src/equipment/Cell.h"
#include "src/equipment/Equipment.h"
#include "src/protocols/mac_layer/AMC/AMCEntity.h"
#include "src/protocols/mac_layer/TransportBlock.h"
#include "src/protocols/Packet.h"
#include "src/equipment/Cell.h"

#include "src/debug.h"


CellMacEntity::CellMacEntity(Cell *cell)
{
    debug("Cell Mac Entity: MAC Entity is created");
    assignCell(cell);
    configMacEntity();
}

void CellMacEntity::createScheduler(Scheduler::SchedulingAlgorithm algo)
{
    _scheduler = new Scheduler(getCell(), algo);
}

Scheduler *CellMacEntity::getScheduler()
{
    return _scheduler;
}

void CellMacEntity::schedule()
{
    getScheduler()->schedule(getCell()->getUserEquipmentContainer());
}

void CellMacEntity::assignCell(Cell *e)
{
    _cell = e;
}

Cell *CellMacEntity::getCell()
{
    return _cell;
}

void CellMacEntity::createAMCEntity()
{
    amcEntity_ = new AMCEntity();
}

void CellMacEntity::setAMCEntity (AMCEntity *amc)
{
    amcEntity_ = amc;
}

AMCEntity* CellMacEntity::getAMCEntity (void)
{
    return amcEntity_;
}

void CellMacEntity::delAMCEntity()
{
    delete amcEntity_;
}

void CellMacEntity::configMacEntity()
{
    createAMCEntity();
}

int CellMacEntity::calculateTransportBlockSize(int packetSize)
{
    // TS 38.214 (g70): Physical Layer Procedures for Data. 5.1.3.2: Transport block size determination 
    // in this case only for PDSCH channel TBS is calculated.
    int transportBlockSize;
    int resourceElementsPerSlot; // for PDSCH channel

    return transportBlockSize;
}

void CellMacEntity::packetsToTransportBlockContainer(QVector<Packet> &packetContainer)
{
    for (auto pack : packetContainer) {
        getCell()->getUserEquipmentContainer();
        TransportBlock tbs(pack);
        transportBlockContainer_.push_back(tbs);
    }
}

QVector<TransportBlock> &CellMacEntity::getTransportBlockContainer()
{
    return transportBlockContainer_;
}
