#include "Bearer.h"

Bearer::Bearer(int id)
{

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