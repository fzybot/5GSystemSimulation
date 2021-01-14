#ifndef USEREQUIPMENT_H
#define USEREQUIPMENT_H

#include <QVector>

#include <src/equipment/equipment.h>


class UserEquipment : public Equipment{
public:



    // Main parameters
    int identity;
    double pathLoss;

    // logistic info
    double stepSize = 0;
    double speed = 0; // By default the UE is stationar[kmph]

    float EIRP;

public:

    UserEquipment(){
        initialParameters();
    }


    void makeStep(){
        this->latitude = this->latitude + stepSize;
        this->longtitude = this->longtitude + stepSize;
    }
    void calculateEIRP(){
        this->EIRP = this->TxPower + this->antennaGain - this->bodyLosses;
    }

private:

    void initialParameters(){
        this->bandwidth = 10;
        this->TxPower = 20;
        this->antennaGain = 0;
        this->otherLosses = 0;
        this->noiseFigure = 7;
        this->reqSINR = -3.3;
        calculateThermalNoise(this->bandwidth);
        this->RxSensitivity = this->thermalNoise + this->noiseFigure + this->reqSINR;
    }
};







#endif // USEREQUIPMENT_H
