#pragma once
#include "Equipment.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"

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

class Cell: public Equipment
{
protected:
    QVector<UserEquipment*> *userEquipmentContainer_;
    gNodeB                  *targetGNodeB_;
    Antenna                 *antenna_;

    RrcEntity       *rrc;
    PdcpEntity      *pdcp;
    RlcEntity       *rlc;
    CellMacEntity   *macEntity_;

    QPair<int, int> coresetRange_;

    

public:
    Cell();

    void attachUE(UserEquipment *ue);
    bool chechUeExistance(UserEquipment *ue);
    QVector<UserEquipment *> *getUserEquipmentContainer();

    void setTargetGNodeB(gNodeB *gNb);
    gNodeB *getTargetGNodeB();

    void setAntenna(Antenna *ant);
    Antenna *getAntenna();

    void createMacEntity();
    void setMacEntity(CellMacEntity *mac);
    CellMacEntity *getMacEntity();

    void schedule();

    void pathLosDetach();
    void detachUeFromCell(int index, int reason);
};
