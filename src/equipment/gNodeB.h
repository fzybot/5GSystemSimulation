#pragma once


#include "Equipment.h"
#include "src/equipment/UserEquipment.h"

#include <QVector>


class gNodeB : public Equipment
{
public:
    int minRxLevel;

    QVector<UserEquipment> currentUsers;
    QVector<UserEquipment> userQueue;

    gNodeB();
};
