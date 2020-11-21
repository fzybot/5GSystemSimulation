#ifndef USEREQUIPMENT_H
#define USEREQUIPMENT_H

#include <src/equipment/equipment.h>


class UserEquipment : public Equipment{
public:

    // Main parameters
    int identity;
    double pathLoss = 0;

    double stepSize = 0;
    double speed = 0; // By default the UE is stationar[kmph]

public:
    void makeStep(){
        this->latitude = this->latitude + stepSize;
        this->longtitude = this->longtitude + stepSize;
    }

    void calculatePathLoss(){

    }
};







#endif // USEREQUIPMENT_H
