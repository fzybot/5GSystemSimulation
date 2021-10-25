#pragma once
#include "src/protocols/Packet.h"

#include <QVector>


class TransportBlock
{

private:
    Packet          packet_;
    int             size_;
    QVector<bool>   tbsData_;


    bool HARQ = false;

public:
    TransportBlock();
    TransportBlock(Packet &packet);

    void setPacket(Packet &packet);
    Packet &getPacket();
};
