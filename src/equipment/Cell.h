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

    CellMacEntity *macEntity_;

public:
    Cell();

    void attachUEs();

    void createMacEntity();
    CellMacEntity *getMacEntity();


};
