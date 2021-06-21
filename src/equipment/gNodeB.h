#ifndef BASESTATION_H
#define BASESTATION_H

#include <src/equipment/equipment.h>
#include <QVector>
#include <QRandomGenerator>
#include <src/equipment/user_equipment.h>
//class UserEquipment;

class gNodeB : public Equipment{
public:

    int PCI;
    int cellIdentity;
    int minRxLevel = -123;

    // user equipments
    //QVector<UserEquipment> currentUsers;
    // User Equipment Queue
    //QVector<UserEquipment> userQueue;


public:

    gNodeB();


private:
    void initialParameters();

};


#endif // BASESTATION_H
