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

void MacEntity::setDevice(Cell *e)
{
    device_ = e;
}

Cell *MacEntity::getDevice()
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

void MacEntity::packetsToTransportBlockContainer(QVector<Packet> &packetContainer)
{
    for (auto pack : packetContainer) {
        TransportBlock tbs(pack);
        transportBlockContainer_.push_back(tbs);
    }
}

QVector<TransportBlock> &MacEntity::getTransportBlockContainer()
{
    return transportBlockContainer_;
}
