#ifndef BASESTATION_H
#define BASESTATION_H

#include <src/equipment/equipment.h>
#include <QVector>
#include <QRandomGenerator>
#include <src/equipment/user_equipment.h>
//class UserEquipment;

class BaseStation : public Equipment{
public:
    // Logistic information
    int PCI;
    int cellIdentity;
    int minRxLevel = -123;

    // user equipments
    //QVector<UserEquipment> currentUsers;
    // User Equipment Queue
    //QVector<UserEquipment> userQueue;


public:

    BaseStation();
    // for now just random vaues is generated as data (imagine + real part of modulated data)
    //TODO: generation algorithm should be writen.
    void generateDataArray();
    //void addUser(UserEquipment user);


private:
    void initialParameters();

};


#endif // BASESTATION_H
