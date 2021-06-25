#pragma once


#include "Equipment.h"
#include "src/equipment/UserEquipment.h"

#include <QVector>

class Cell;

class gNodeB : public Equipment
{
public:



private:
    int minRxLevel;


    QVector<UserEquipment*> currentUsers;
    QVector<UserEquipment*> userQueue;

    gNodeB();
};
