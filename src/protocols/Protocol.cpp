#include "Protocol.h"
#include "src/equipment/Equipment.h"

Protocol::Protocol()
{

}

void Protocol::setDevice(Equipment *e){
    device_ = e;
}

Equipment* Protocol::getDevice(){
    return device_;
}