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
    QVector<UserEquipment*> *firstQueue_;
    QVector<UserEquipment*> *timeQueue_;
    QVector<UserEquipment*> *freqQueue_;

private:
    int nPRB_ = 0;
    int nAvailablePRB_ = 0;
    int maxNumberOfScheuledUE_ = 10;

public:
    Scheduler();

    void doSchedule(QVector<UserEquipment*> *userEquipmentContainer);

    void setCell(Cell *cell);
    Cell *getCell();

    void setAlgorithm(SchedulingAlgorithm algo);
    SchedulingAlgorithm getAlgorithm();

    void timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer);
    void frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer);

    // Scheduling algorithms
    void roundRobin(QVector<UserEquipment*> *userEquipmentContainer);
    void propotionalFair(QVector<UserEquipment*> *userEquipmentContainer);

    // Support methods
    void updateAvailableNumPRB(int nPRB);
    int getAvailableNumPRB();

    // TODO: finish these methods
    void checkMeasGap(QVector<UserEquipment*> *userEquipmentContainer);
    void checkDRX(QVector<UserEquipment*> *userEquipmentContainer);
    void checkTransmitSlot(QVector<UserEquipment *> *userEquipmentContainer);

    void addToQueue(int id);
    
};
