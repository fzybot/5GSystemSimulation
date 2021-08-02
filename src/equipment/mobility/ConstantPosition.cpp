#include "ConstantPosition.h"

ConstantPosition::ConstantPosition()
{
    setMobilityModel(Mobility::CONSTANT_POSITION);
    setPosition(nullptr);
}

ConstantPosition::~ConstantPosition()
{
    deletePosition();
}

void ConstantPosition::updatePosition(double time)
{
    
}