#pragma once


#include "Equipment.h"
#include "src/equipment/UserEquipment.h"

#include <QVector>


class Cell;
class Mobility;
class CellMacEntity;
class Scheduler;

class gNodeB : public Equipment
{

private:
    int minRxLevel;

    QVector<UserEquipment*> *userEquipmentContainer_;
    QVector<Cell*> *cellContainer_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    gNodeB();
    gNodeB(int ID, Cell *cell, double posX, double posY, double posZ);
    gNodeB(int ID, double posX, double posY, double posZ);

// ----- [ GETTERS\SETTERS ] -------------------------------------------------------------------------------------------
    // get Containers
    QVector<UserEquipment*> *getUserEquipmentContainer (void);
    QVector<Cell*> *getCellContainer (void);

    void addCell(Cell *cell);
    Cell *getCellByID(int ID);
};
