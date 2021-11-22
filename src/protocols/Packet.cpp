#include "Packet.h"
#include "src/protocols/bearers/RadioBearer.h"

Packet::Packet()
{
    bearer_ = new RadioBearer();
}

Packet::Packet(QVector<bool> data, double timeStamp, int id)
{
    data_ = data;
    id_ = id;
    timeStamp_ = timeStamp;
    size_ = data.size();
    /*
    m_RTPHeader = nullptr;
    m_UDPHeader = nullptr;
    m_IPHeader = nullptr;
    m_SDAPHeader = nullptr;
    m_PDCPHeader = nullptr;
    m_RLCHeader = nullptr;
    m_MACHeader = nullptr;
    */
}

Packet::Packet(int size, double timeStamp, int id)
{
    size_ = size;
    timeStamp_ = timeStamp;
    id_ = id;
}

Packet::Packet(int size, int slot, int id, RadioBearer *bearer)
{
    size_ = size;
    timeSlotGenerated_ = slot;
    timeSlotToTransmit_ = slot;
    id_ = id;
    setBearer(bearer);
}

Packet::~Packet()
{
    /*
    delete m_RTPHeader;
    delete m_UDPHeader;
    delete m_IPHeader;
    delete m_SDAPHeader;
    delete m_PDCPHeader;
    delete m_RLCHeader;
    delete m_MACHeader;
    */
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
    size_ = size * 8;
}

int Packet::getSize()
{
    return size_ + (headerSize_ * 8);
}

int Packet::getSizeBits()
{
    return getSize();
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