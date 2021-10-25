#pragma once
#include "src/protocols/Packet.h"

#include <QVector>


class TransportBlock
{

private:
    Packet          packet_;
    int             size_ = 0;
    QVector<bool>   tbsData_;
    QVector<Packet> packetContainer_;

    bool HARQ = false;

public:
    TransportBlock();
    TransportBlock(Packet &packet);

    void setPacket(Packet &packet);
    Packet &getPacket();

    void appendPacket(Packet Packet);
    QVector<Packet> &getPacketContainer();

    void addSize(int size);
    int getSize();
};
