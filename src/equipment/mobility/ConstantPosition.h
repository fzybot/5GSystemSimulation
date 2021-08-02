#pragma once
#include "src/equipment/mobility/Mobility.h"

class ConstantPosition: public Mobility
{
public:
    ConstantPosition();
    virtual ~ConstantPosition();

    virtual void updatePosition(double time);
};
