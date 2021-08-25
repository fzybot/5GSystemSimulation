#pragma once
#include "Equipment.h"

#include <QVector>

class UserEquipment;
class CellMacEntity;
class gNodeB;

class Cell: public Equipment
{
protected:
    QVector<UserEquipment*> *userEquipmentContainer_;
    gNodeB *targetGNodeB_;

    CellMacEntity *macEntity_;

public:
    Cell();

    void attachUE(UserEquipment *ue);
    QVector<UserEquipment*> *getUserEquipmentContainer (void);

    void setTargetGNodeB(gNodeB *gNb);
    gNodeB *getTargetGNodeB();


    void createMacEntity();
    CellMacEntity *getMacEntity();
};
