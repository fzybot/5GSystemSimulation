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

void TransportBlock::appendPacket(Packet *packet, int size)
{
    packetContainer_.push_back(packet);
    addSize(size);
    addSizeWoCodeRate(packet->getSize());
}

QVector<Packet*> &TransportBlock::getPacketContainer()
{
    return packetContainer_;
}

void TransportBlock::setSize(int size)
{
    sizeCodeRate_ = size;
}

void TransportBlock::addSize(int size)
{
    sizeCodeRate_ += size;
}

int TransportBlock::getSize()
{
    return sizeCodeRate_; // 200 - overheads
}

void TransportBlock::setSizeWoCodeRate(int size)
{
    size_ = size;
}

void TransportBlock::addSizeWoCodeRate(int size)
{
    size_ += size;
}

int TransportBlock::getSizeWoCodeRate()
{
    return size_;
}

void TransportBlock::clear()
{
    packetContainer_.clear();
    setSize(0);
    setSizeWoCodeRate(0);
}

void TransportBlock::setNumberOfPrb(int number)
{
    nPrb_ = number;
}

int TransportBlock::getNumberOfPrb()
{
    return nPrb_;
}
