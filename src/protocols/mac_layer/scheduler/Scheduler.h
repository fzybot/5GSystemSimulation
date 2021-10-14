#pragma once
#include <QVector>

class UserEquipment;
class Cell;
class gNodeB;

class Scheduler
{
public:
    enum class SchedulingAlgorithm
    {
      ROUND_ROBIN,
      PROPOTIONAL_FAIR,
    };

protected:
    SchedulingAlgorithm     algorithm_;
    Cell                    *cell_;
    QVector<int>            *firstQueue_;
    QVector<int>            *timeQueue_;
    QVector<int>            *freqQueue_;

public:
    Scheduler();

    void doSchedule(QVector<UserEquipment*> *userEquipmentContainer);

    void setCell(Cell *cell);
    Cell *getCell();

    void setAlgorithm(SchedulingAlgorithm algo);
    SchedulingAlgorithm getAlgorithm();

    void timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer);
    void frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer);

    void roundRobin(QVector<UserEquipment*> *userEquipmentContainer);
    void propotionalFair(QVector<UserEquipment*> *userEquipmentContainer);

    void checkMeasGap(QVector<UserEquipment*> *userEquipmentContainer);
    void checkDRX(QVector<UserEquipment*> *userEquipmentContainer);
    void checkTransmitSlot(QVector<UserEquipment *> *userEquipmentContainer);

    void addToQueue(int id);
    
};
