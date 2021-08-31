#pragma once

#include <QVector>
#include <QBitArray>
#include "src/protocols/Protocol.h"
class Equipment;
class AMCEntity;
class HARQEntity;

class MacEntity
{
protected:
    // Connected Entities
    Equipment *device_;
    AMCEntity *amcEntity_;
    HARQEntity *harqEntity_;

    // Data transmission
    QVector<int> *dataBuffer_;

    // PHY configuration
    QVector< QVector< QBitArray > > *resourceElementMatrix; // per 1 slot
    int CORESETS_size_;
    int BWP_size_;

    // KPIs
    int dataTransmitted; // [bits]
    int macThroughput;

public:
    MacEntity();
    virtual ~MacEntity() {};

    void setDevice(Equipment *e);
    Equipment *getDevice();

    void createAMCEntity();
    void setAMCEntity(AMCEntity *amc);
    AMCEntity *getAMCEntity (void);
    void delAMCEntity();

    //TODO: Deal with the scheduler
    //void createShcedulerEntity();

    void configMacEntity();
};
