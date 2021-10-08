#pragma once
#include "src/protocols/bearers/Bearer.h"
#include "src/equipment/QoS/QoSProfile.h"
#include "src/protocols/Packet.h"

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

    int id_;
    double ambr;

    QoSProfile *QoS_;

    QVector<Packet> packetsInBuffer_;

public:
    RadioBearer();
    RadioBearer(int id);

    void setId(int id);
    int getId();

    void setQoSProfile(QoSProfile *QoS);
    QoSProfile *getQoSProfile();

    void createDefaultBearer(int id);
    void createRadioBearer(RadioBearerType type, int id, int QoSProfile);

    void generatePackets(int number, int currentSlot);
    QVector<Packet> &getPacketsContainer();
};
