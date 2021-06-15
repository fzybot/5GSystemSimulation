#ifndef USEREQUIPMENT_H
#define USEREQUIPMENT_H

#include <QVector>

#include <src/equipment/equipment.h>
#include <src/equipment/gNodeB.h>
//class BaseStation;

class UserEquipment : public Equipment{
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

private:
    void initialParameters();
};







#endif // USEREQUIPMENT_H
