#include "TransportBlock.h"

TransportBlock::TransportBlock()
{
 
}

TransportBlock::TransportBlock(Packet &packet)
{
    setPacket(packet);
}

void TransportBlock::setPacket(Packet &packet)
{
    packet_ = packet;
}

Packet &TransportBlock::getPacket()
{
    return packet_;
}