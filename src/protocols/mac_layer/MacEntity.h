#pragma once

#include <QVector>

class Equipment;
class AMCEntity;
class HARQEntity;

class MacEntity
{
protected:
    Equipment* m_device;
    AMCEntity *amcEntity_;
    HARQEntity *harqEntity_;

public:
    MacEntity();
    virtual ~MacEntity() {};

    void setDevice(Equipment *e);
    Equipment* getDevice();

    void createAMCEntity();
    void setAMCEntity(AMCEntity *amc);
    AMCEntity* getAMCEntity (void);
    void delAMCEntity();

    //TODO: Deal with the scheduler
    //void createShcedulerEntity();


    void configMacEntity();


};
