#include "RadioBearer.h"

RadioBearer::RadioBearer()
{

}

void RadioBearer::createDefaultBearer(int id)
{
    setId(id);
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