#include "Bearer.h"

Bearer::Bearer()
{

}

Bearer::Bearer(int id)
{
    setId(id);
}

int Bearer::getQci()
{
    return qci_;
}

void Bearer::setId(int id)
{
    id_ = id;
}

int Bearer::getId()
{
    return id_;
}
