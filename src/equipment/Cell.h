#pragma once
#include "Equipment.h"

#include <QVector>

class UserEquipment;
class RrcEntity;
class PdcpEntity;
class RlcEntity;
class CellMacEntity;
class Phy;
class gNodeB;
class Antenna;

class Cell: public Equipment
{
protected:
    QVector<UserEquipment*> *userEquipmentContainer_;
    gNodeB *targetGNodeB_;
    Antenna *antenna_;

    CellMacEntity *macEntity_;


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
};
