#include "MacEntity.h"

MacEntity::MacEntity()
{

}

void MacEntity::setDevice(Equipment *e){
    m_device = e;
}

Equipment* MacEntity::getDevice(){
    return m_device;
}
