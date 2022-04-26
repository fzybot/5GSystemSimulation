#include "MacEntity.h"

#include "src/equipment/Equipment.h"
#include "src/protocols/mac_layer/AMC/AMCEntity.h"
#include "src/protocols/mac_layer/TransportBlock.h"
#include "src/protocols/Packet.h"
#include "src/equipment/Cell.h"

#include "src/debug.h"

MacEntity::MacEntity()
{
    debug("Mac Entity: MAC Entity is created");
}

void MacEntity::assignCell(Cell *e)
{
    device_ = e;
}

Cell *MacEntity::getCell()
{
    return device_;
}

void MacEntity::createAMCEntity()
{
    amcEntity_ = new AMCEntity();
}

void MacEntity::setAMCEntity (AMCEntity *amc)
{
    amcEntity_ = amc;
}

AMCEntity* MacEntity::getAMCEntity (void)
{
    return amcEntity_;
}

void MacEntity::delAMCEntity()
{
    delete amcEntity_;
}

void MacEntity::configMacEntity()
{
    createAMCEntity();
}

int calculateTransportBlockSize(int packetSize)
{
    // TS 38.214 (g70): Physical Layer Procedures for Data. 5.1.3.2: Transport block size determination 
    // in this case only for PDSCH channel TBS is calculated.
    int transportBlockSize;
    int resourceElementsPerSlot; // for PDSCH channel

    return transportBlockSize;
}

void MacEntity::packetsToTransportBlockContainer(QVector<Packet> &packetContainer)
{
    for (auto pack : packetContainer) {
        getCell()->getUserEquipmentContainer();
        TransportBlock tbs(pack);
        transportBlockContainer_.push_back(tbs);
    }
}

QVector<TransportBlock> &MacEntity::getTransportBlockContainer()
{
    return transportBlockContainer_;
}
