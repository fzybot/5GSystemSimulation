#pragma once

#include <QVector>

class Equipment;
class AMCEntity;

class MacEntity
{
private:
    Equipment* m_device;
    AMCEntity *amcEntity_;

public:
    MacEntity();
    virtual ~MacEntity() {};

    void setDevice(Equipment *e);
    Equipment* getDevice();

    void setAMCEntity (AMCEntity * amc);
    AMCEntity* getAMCEntity (void);
};
