#include "Bearer.h"

Bearer::Bearer()
{

}

Bearer::Bearer(int id)
{
    setId(id);
}

void Bearer::setId(int id)
{
    id_ = id;
}

int Bearer::getId()
{
    return id_;
}

void Bearer::setQoSProfile(QoSProfile *QoS)
{
    QoS_ = QoS;
}
QoSProfile *Bearer::getQoSProfile()
{
    return QoS_;
}