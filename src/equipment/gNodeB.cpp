#include "gNodeB.h"


gNodeB::gNodeB(){
    initialParameters();
    this->dataSize = ( ((this->bandwidth * 1000) / this->SCS ) * 2 * 14 * mimoLayers );
    generateDataArray();
}

void gNodeB::generateDataArray(){
    for (int i = 0; i < this->dataSize; i++){
        this->data.append(QRandomGenerator::global()->generateDouble());
    }
}

//void BaseStation::addUser(UserEquipment user){
//    this->currentUsers.push_back(user);
//}

void gNodeB::initialParameters(){
    this->PCI = 123;
    this->TxPower = 43;
    this->antennaGain = 18;
    this->otherLosses = 0;
    this->noiseFigure = 3;
    this->reqSINR = -3.3;
    this->bandwidth = 10;
    calculateThermalNoise();
    this->RxSensitivity = this->thermalNoise + this->noiseFigure + this->reqSINR;
    calculateEIRP();

    this->height = 60;

}
