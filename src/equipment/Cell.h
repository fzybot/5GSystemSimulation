#pragma once
#include "Equipment.h"

#include <QVector>
#include <QPair>

class UserEquipment;
class RrcEntity;
class PdcpEntity;
class RlcEntity;
class CellMacEntity;
class Physical;
class gNodeB;
class Antenna;
class Scheduler;

class Cell: public Equipment
{
protected:
    QVector<UserEquipment*> *userEquipmentContainer_;
    gNodeB *targetGNodeB_;
    Antenna *antenna_;

    RrcEntity *rrc;
    PdcpEntity *pdcp;
    RlcEntity *rlc;
    CellMacEntity *macEntity_;
    Physical *phyEntity_;

    Scheduler *scheduler_;

    QPair<int, int> coresetRange_;

public:
    Cell();

    void attachUE(UserEquipment *ue);
    QVector<UserEquipment*> *getUserEquipmentContainer (void);

    void setTargetGNodeB(gNodeB *gNb);
    gNodeB *getTargetGNodeB();

    void setAntenna(Antenna *ant);
    Antenna *getAntenna();

    void createPhyEntity();
    void setPhyEntity(Physical *phy);
    Physical *getPhyEntity();

    void createMacEntity();
    void setMacEntity(CellMacEntity *mac);
    CellMacEntity *getMacEntity();

    void createScheduler();
    void setScheduler(Scheduler *scheduler);
    Scheduler *getScheduler();
};
