#include "MacEntity.h"

#include "src/equipment/Equipment.h"
#include "src/protocols/mac_layer/AMC/AMCEntity.h"

#include "src/debug.h"

MacEntity::MacEntity()
{
    debug("Mac Entity: MAC Entity is created");
}

void MacEntity::setDevice(Equipment *e){
    device_ = e;
}

Equipment* MacEntity::getDevice(){
    return device_;
}

void MacEntity::createAMCEntity()
{
    amcEntity_ = new AMCEntity();
}

void MacEntity::setAMCEntity (AMCEntity *amc)
{
    amcEntity_ = amc;
}

AMCEntity* MacEntity::getAMCEntity (void)
{
    return amcEntity_;
}

void MacEntity::delAMCEntity()
{
    delete amcEntity_;
}

void MacEntity::configMacEntity()
{
    createAMCEntity();
}
