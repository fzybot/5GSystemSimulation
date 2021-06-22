#pragma once


#include "Equipment.h"
#include "src/equipment/UserEquipment.h"

#include <QVector>


class gNodeB : public Equipment
{
public:
    int PCI;
    int ID;
    int minRxLevel;

    QVector<UserEquipment> currentUsers;
    QVector<UserEquipment> userQueue;

    gNodeB();
};
