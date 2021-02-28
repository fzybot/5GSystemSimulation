#include "user_equipment.h"

UserEquipment::UserEquipment(){
    initialParameters();
}

void UserEquipment::initialParameters(){
    this->bandwidth = 10;
    this->TxPower = 23;
    this->antennaGain = 0;
    this->otherLosses = 0;
    this->noiseFigure = 7;
    this->reqSINR = -3.3;
    calculateThermalNoise();
    this->RxSensitivity = this->thermalNoise + this->noiseFigure + this->reqSINR;
    calculateEIRP();

    this->height = 1.5;
}

void UserEquipment::makeStep(){
    this->latitude = this->latitude + stepSize;
    this->longtitude = this->longtitude + stepSize;
}

void UserEquipment::calculateStepSize(){
    // 0.00001 - equal to 1 meter
    this->stepSize = round(this->speed * 1000 / 3600) * 0.00001;
}

void UserEquipment:: calculateEIRP(){
    this->EIRP = this->TxPower - this->bodyLosses;
}
