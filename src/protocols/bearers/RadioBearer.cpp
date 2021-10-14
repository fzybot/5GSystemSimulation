#include "RadioBearer.h"
#include "src/protocols/bearers/QoS/QoSProfile.h"
#include "src/protocols/Packet.h"
#include "src/protocols/bearers/ServiceTrafficProfile.h"

#include <QRandomGenerator>
#include <QDebug>

RadioBearer::RadioBearer()
{
    QoS_ = new QoSProfile();
}

void RadioBearer::createDefaultBearer(int id)
{
    setId(id);
    type_ = RadioBearerType::DRB;
    getQoSProfile()->set5QIValue(8);
}

void RadioBearer::createRadioBearer(RadioBearerType type, int id, int QoSProfile)
{
    type_ = type;
    setId(id);
    getQoSProfile()->set5QIValue(QoSProfile);
}

void RadioBearer::setId(int id)
{
    id_ = id;
}

int RadioBearer::getId()
{
    return id_;
}

void RadioBearer::setQoSProfile(QoSProfile *QoS)
{
    QoS_ = QoS;
}

QoSProfile *RadioBearer::getQoSProfile()
{
    return QoS_;
}

void RadioBearer::setTrafficProfile(ServiceTrafficProfile::Profile profile)
{

}

ServiceTrafficProfile &RadioBearer::getTrafficProfile()
{
    return trafficProfile_;
}

int &RadioBearer::getCounterDataTransmitted()
{
    return counterDataTransmitted_;
}
int &RadioBearer::getCounterSlotTransmitted()
{
    return counterSlotTransmitted_;
}
