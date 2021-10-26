#include "TransportBlock.h"
#include "src/protocols/Packet.h"

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

void TransportBlock::appendPacket(Packet Packet)
{
    packetContainer_.push_back(Packet);
    addSize(Packet.getSize());
}

QVector<Packet> &TransportBlock::getPacketContainer()
{
    return packetContainer_;
}

void TransportBlock::addSize(int size)
{
    size_ += size;
}

int TransportBlock::getSize()
{
    return size_;
}