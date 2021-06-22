#pragma once


#include "src/equipment/Equipment.h"

#include <QVector>


class UserEquipment : public Equipment
{
private:
    void initialParameters();

public:
    // Main parameters
    int identity;
    double pathLoss;

    // logistic info
    double stepSize;
    double speed; // By default the UE is stationar[kmph]

    //neighbour base stations
    //QVector<BaseStation> neighbourCells;


public:
    UserEquipment();

    void makeStep();
    void calculateEIRP();
    void calculateStepSize();

    //void addNeighbourCell(BaseStation cell);
};
