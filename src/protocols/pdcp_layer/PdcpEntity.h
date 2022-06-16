#pragma once

#include "src/protocols/Packet.h"

class PdcpEntity
{
private:
    int _headerSize = 20; // [byte]
    int _size;

    Packet *_packet;

public:
    PdcpEntity();
    PdcpEntity(Packet *packet);

    void packetToPdu(Packet *packet);
    Packet *getPacket();

    int getSize();
};
