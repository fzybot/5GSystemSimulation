#pragma once


#include "src/equipment/Equipment.h"

#include <QVector>

class gNodeB;
class Cell;

class UserEquipment : public Equipment
{

private:
    gNodeB *targetGNodeB_;
    Cell *currentCell_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    UserEquipment();
    UserEquipment(int id, 
                  double posX, double posY, double posZ, 
                  Cell *cell, gNodeB *targetGNodeB, 
                  Mobility::MobilityModel model);

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setCurrentCell(Cell *cell);
    void setTargetGNodeB(gNodeB *gNb);

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
    void calculateEIRP();

    //void addNeighbourCell(BaseStation cell);
};
