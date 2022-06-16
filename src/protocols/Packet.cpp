
#include <QRandomGenerator>
#include <functional>
#include <random>
#include <QDebug>

#include "Packet.h"
#include "src/protocols/bearers/RadioBearer.h"

Packet::Packet()
{
    bearer_ = new RadioBearer();
}

Packet::Packet(int size, double timeStamp, int id)
{
    size_ = size;
    timeStamp_ = timeStamp;
    id_ = id;
}

Packet::Packet(int size, int slot, int id, RadioBearer *bearer)
{
    setSize(size);
    timeSlotGenerated_ = slot;
    timeSlotToTransmit_ = slot;
    setId(id);
    setBearer(bearer);
    generateRandomData();
}

Packet::Packet(QVector<bool> &data, Packet *parent, QVector<Packet *> &buffer)
{
    copyData(data);
    setParent(parent);
    buffer.push_back(this);
}

Packet::~Packet()
{

}

bool Packet::isParent()
{
    return _isParent;
}

void Packet::setParent(Packet *parent)
{
    _parent = parent;
    _isParent = false;
    setId(parent->getId());
    setSlotGenerated(parent->getSlotGenerated());
    setSlotToTransmit(parent->getSlotToTransmit());
    setBearer(parent->getBearer());
}

Packet *Packet::getParent()
{
    return _parent;
}

void Packet::setId(int pId)
{
    id_ = pId;
}

int Packet::getId()
{
    return id_;
}

void Packet::setTimeStamp(double time)
{
    timeStamp_ = time;
}

double Packet::getTimeStamp()
{
    return timeStamp_;
}

void Packet::setHeaderSize(int s)
{
    headerSize_ = s;
}

int Packet::getHeaderSize()
{
    return headerSize_;
}

void Packet::addHeaderSize(int s)
{
    size_ += s;
}

void Packet::setSize(int size)
{
    size_ = size;
}

int Packet::getSize()
{
    return size_;
}

int Packet::getSizeBits()
{
    return getSize() * 8;
}

void Packet::setSlotGenerated(int slot)
{
    timeSlotGenerated_ = slot;
}

int Packet::getSlotGenerated()
{
    return timeSlotGenerated_;
}

void Packet::setSlotToTransmit(int slot)
{
    timeSlotToTransmit_ = slot;
}

int Packet::getSlotToTransmit()
{
    return timeSlotToTransmit_;
}

void Packet::setSlotTransmitted(int transmittedSlot)
{
    timeSlotTransmitted_ = transmittedSlot;
}

int Packet::getSlotTransmitted()
{
    return timeSlotTransmitted_;
}

void Packet::setBearer(RadioBearer *bearer)
{
    bearer_ = bearer;
}

RadioBearer *Packet::getBearer()
{
    return bearer_;
}

void Packet::copyData(QVector<bool> &data)
{
    data_.clear();
    for (int i = 0; i < data.size(); i ++){
        data_.push_back(data[i]);
    }
    setSize(data.size());
}

QVector<bool> &Packet::getData()
{
    return data_;
}

void Packet::generateRandomData()
{
    QRandomGenerator generator;
    for (int i = 0; i < getSizeBits(); i ++){
        int val = generator.bounded(0, 2);
        data_.push_back(val);
    }
}
