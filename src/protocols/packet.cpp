#include "Packet.h"


Packet::Packet(QVector<bool> data, double timeStamp, int id) :
    m_data(data),
    m_id(id),
    m_timeStamp(timeStamp),
    m_size(data.size())
{
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
    m_timeStamp = time;
}

double Packet::getTimeStemp()
{
    return m_timeStamp;
}

void Packet::addHeaderSize(int s)
{
    m_size += s;
}
