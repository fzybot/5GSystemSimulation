#pragma once
#include "src/protocols/bearers/Bearer.h"
#include "src/protocols/QoS/QoSProfile.h"
#include "src/protocols/Packet.h"
#include "src/protocols/ServiceTrafficProfile.h"

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
    ServiceTrafficProfile  trafficProfile_;
    QVector<Packet> packetsInBuffer_;

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
    QVector<Packet> &getPacketsContainer();

    int &getCounterDataTransmitted();
    int &getCounterSlotTransmitted();
};
