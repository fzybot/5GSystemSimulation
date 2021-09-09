#include "RadioBearer.h"

RadioBearer::RadioBearer()
{

}

void RadioBearer::createDefaultBearer(int id)
{
    setId(id);
    qci_ = 5;
    type_ = RadioBearerType::DRB;
}