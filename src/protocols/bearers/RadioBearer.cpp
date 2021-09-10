#include "RadioBearer.h"

RadioBearer::RadioBearer()
{

}

void RadioBearer::createDefaultBearer(int id)
{
    setId(id);
    type_ = RadioBearerType::DRB;
}
