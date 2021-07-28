#pragma once


#include "src/equipment/Equipment.h"


class MacEntity
{
public:
    Equipment* m_device;


    MacEntity();

    void setDevice(Equipment* e);
    Equipment* getDevice();

    virtual ~MacEntity() {};
};
