#include "Packet.h"

Packet::Packet()
{
    
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

Packet::Packet(int size, int slot, int id)
{
    size_ = size;
    slotToTransmit_ = slot;
    id_ = id;
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

double Packet::getTimeStemp()
{
    return timeStamp_;
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