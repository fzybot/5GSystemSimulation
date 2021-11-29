#pragma once


#include "src/protocols/bearers/QoS/QoSProfile.h"
#include "src/protocols/bearers/ServiceTrafficProfile.h"
#include "src/protocols/Packet.h"

#include <QVector>
#include <QQueue>

class Packet;

class RadioBearer
{
public:
    enum class RadioBearerType
    {
      SRB0,
      SRB1,
      SRB2,
      DRB
    };

private:
    RadioBearer::RadioBearerType type_;

    int             id_;
    double          ambr_;
    QoSProfile      *QoS_;

    ServiceTrafficProfile   trafficProfile_;

    QVector<Packet*>    packetsInBuffer_;
    QVector<Packet*>    packetsCurrentSlot_;
    QQueue<Packet*>     packetsQueueCurrentSlot_;

    int                 gPacketId_ = 1000;
    int                 bufferSize_ = 0;

    // COUNTERS 
    int counterDataTransmitted_;
    int counterSlotTransmitted_;

public:
    RadioBearer();
    RadioBearer(int id);

    void setId(int id);
    int getId();

    void setQoSProfile(QoSProfile *QoS);
    QoSProfile *getQoSProfile();

    void createDefaultBearer(int id);
    void createRadioBearer(RadioBearerType type, int id, int QoSProfile);

    void setTrafficProfile(ServiceTrafficProfile::Profile profile);
    ServiceTrafficProfile &getTrafficProfile();

    void generatePackets(int number, int currentSlot);
    QVector<Packet*> &getPacketsContainer();
    QVector<Packet*> &getPacketsContainerCurrentSlot(int slot);
    void deletePackets(QVector<Packet*> &packetsToDelete);
    void deletePacket(Packet *packetToDelete);
    void showPacketsInBuffer();
    void updatePacketTransmitSlot(int slot);

    void addToBuffer(int size);
    void decreaseBuffer(int decSize);
    int getBufferSize();

    int &getCounterDataTransmitted();
    int &getCounterSlotTransmitted();
};
