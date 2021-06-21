#pragma once


#include "Equipment.h"
#include "src/equipment/UserEquipment.h"

#include <QVector>
#include <QRandomGenerator>


class gNodeB : public Equipment
{
private:
    void initialParameters();

public:
    int PCI;
    int gNodeBId;
    int minRxLevel;

    // user equipments
    //QVector<UserEquipment> currentUsers;
    // User Equipment Queue
    //QVector<UserEquipment> userQueue;


    gNodeB();
};
