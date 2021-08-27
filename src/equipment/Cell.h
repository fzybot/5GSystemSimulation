#pragma once
#include "Equipment.h"

#include <QVector>

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
    gNodeB *targetGNodeB_;
    Antenna *antenna_;

    RrcEntity *rrc;
    PdcpEntity *pdcp;
    RlcEntity *rlc;
    CellMacEntity *macEntity_;
    Physical *phyEntity_;

public:
    Cell();

    void attachUE(UserEquipment *ue);
    QVector<UserEquipment*> *getUserEquipmentContainer (void);

    void setTargetGNodeB(gNodeB *gNb);
    gNodeB *getTargetGNodeB();

    void setAntenna(Antenna *ant);
    Antenna *getAntenna();

    void createMacEntity();
    CellMacEntity *getMacEntity();

    void setPhyEntity();
    Physical *getPhyEntity();
};
