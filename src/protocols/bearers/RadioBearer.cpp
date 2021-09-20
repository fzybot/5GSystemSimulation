#include "RadioBearer.h"
#include "src/equipment/QoS/QoSProfile.h"

RadioBearer::RadioBearer()
{
    QoS_ = new QoSProfile();
}

void RadioBearer::createDefaultBearer(int id)
{
    setId(id);
    getQoSProfile()->set5QIValue(8);
    type_ = RadioBearerType::DRB;
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