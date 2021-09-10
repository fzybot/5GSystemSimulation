#pragma once
#include <QVector>

class UserEquipment;
class Cell;
class gNodeB;

class Scheduler
{
protected:
    Cell *cell_;

public:
    Scheduler();

    void doSchedule(QVector<UserEquipment*> *userEquipmentContainer);

    void setCell(Cell *cell);
    Cell *getCell();
};
