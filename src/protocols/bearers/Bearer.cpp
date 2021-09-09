#include "Bearer.h"

Bearer::Bearer()
{

}

Bearer::Bearer(int id)
{
    id_ = id;
}

void Bearer::createDefaultBearer(int id)
{
    id_ = id;
    qci_ = 5;
    type_ = BearerType::DRB;
}

int Bearer::getQci()
{
    return qci_;
}

int Bearer::getId()
{
    return id_;
}