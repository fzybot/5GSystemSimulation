#include "ConstantPosition.h"
#include "src/debug.h"

ConstantPosition::ConstantPosition()
{
    debug("ConstantPosition: creating new object");
    setModel(Mobility::Model::CONSTANT_POSITION);
    //setPosition(nullptr);
}

ConstantPosition::~ConstantPosition()
{
    deletePosition();
}

void ConstantPosition::updatePosition(double time)
{
    
}
