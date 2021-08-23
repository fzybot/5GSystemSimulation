#pragma once

#include <QVector>

class Equipment;

class MacEntity
{
private:
    Equipment* m_device;

public:
    MacEntity();
    virtual ~MacEntity() {};

    void setDevice(Equipment *e);
    Equipment* getDevice();
};
