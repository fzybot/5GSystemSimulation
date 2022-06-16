

#include "PdcpEntity.h"
#include "src/protocols/Packet.h"


PdcpEntity::PdcpEntity()
{

}

PdcpEntity::PdcpEntity(Packet *packet)
{
    packetToPdu(packet);
}

void PdcpEntity::packetToPdu(Packet *packet)
{
    _packet = packet;
    _size = packet->getSize() + _headerSize;
}

Packet *PdcpEntity::getPacket()
{
    return _packet;
}

int PdcpEntity::getSize()
{
    return _size;
}
