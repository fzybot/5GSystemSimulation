#include "RadioBearer.h"
#include "src/equipment/QoS/QoSProfile.h"

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