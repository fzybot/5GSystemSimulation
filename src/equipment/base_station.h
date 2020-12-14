#ifndef BASESTATION_H
#define BASESTATION_H

#include <src/equipment/equipment.h>
#include <QVector>
#include <src/equipment/user_equipment.h>


class BaseStation : public Equipment{
public:

    // Logistic information
    int PCI;
    int cellIdentity;

    // user equipments
    QVector<UserEquipment> currentUsers;

    // data Queue
    QVector<int> dataQueue;

public:
    BaseStation(){
        this->PCI = 123;
    }
private:
    void addUser(UserEquipment user){
        this->currentUsers.push_back(user);
    }
};


#endif // BASESTATION_H
