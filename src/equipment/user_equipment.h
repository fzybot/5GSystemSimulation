#ifndef USEREQUIPMENT_H
#define USEREQUIPMENT_H

#include <QVector>

#include <src/equipment/equipment.h>


class UserEquipment : public Equipment{
public:



    // Main parameters
    int identity;
    double pathLoss = 0;

    // logistic info
    double stepSize = 0;
    double speed = 0; // By default the UE is stationar[kmph]

public:

    UserEquipment(){
        this->TxPower = 20;
        this->antennaGain = 0;
        this->otherLosses = 12;
        this->noiseFigure = 7;
        this->reqSINR = -3.3;
        this->RxSensitivity = this->thermalNoise + this->noiseFigure + this->reqSINR;
    }


    void makeStep(){
        this->latitude = this->latitude + stepSize;
        this->longtitude = this->longtitude + stepSize;
    }

    void calculateStep(double TTI){
        this->stepSize =  0;
    }

    void calculatePathLoss(){

    }
};







#endif // USEREQUIPMENT_H
