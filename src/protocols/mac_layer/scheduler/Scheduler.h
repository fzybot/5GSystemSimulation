#pragma once
#include <QVector>

class UserEquipment;
class Cell;
class gNodeB;

class Scheduler
{
protected:
    Cell *cell_;
    QVector<int> *firstQueue_;
    QVector<int> *timeQueue_;
    QVector<int> *freqQueue_;

public:
    Scheduler();

    void doSchedule(QVector<UserEquipment*> *userEquipmentContainer);

    void setCell(Cell *cell);
    Cell *getCell();

    void timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer);
    void frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer);

    void addToQueue(int id);
    
};
