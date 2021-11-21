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

void TransportBlock::appendPacket(Packet *packet)
{
    packetContainer_.push_back(packet);
    addSize(packet->getSize());
}

QVector<Packet*> &TransportBlock::getPacketContainer()
{
    return packetContainer_;
}

void TransportBlock::setSize(int size)
{
    size_ = size;
}

void TransportBlock::addSize(int size)
{
    size_ += size;
}

int TransportBlock::getSize()
{
    return size_;
}

void TransportBlock::clear()
{
    packetContainer_.clear();
    size_ = 0;
}
