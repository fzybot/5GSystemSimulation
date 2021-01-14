#ifndef BASESTATION_H
#define BASESTATION_H

#include <src/equipment/equipment.h>
#include <QVector>
#include <QRandomGenerator>
#include <src/equipment/user_equipment.h>


class BaseStation : public Equipment{
public:

    // Logistic information
    int PCI;
    int cellIdentity;

    // user equipments
    QVector<UserEquipment> currentUsers;

    // User Equipment Queue
    QVector<UserEquipment> userQueue;

public:

    BaseStation(){
        initialParameters();
        this->dataSize = ( ((this->bandwidth * 1000) / this->SCS ) * 2 * 14 * mimoLayers );
        generateDataArray();
    }

    // for now just random vaues is generated as data (imagine + real part of modulated data)
    //TODO: generation algorithm should be writen.
    void generateDataArray(){
        for (int i = 0; i < this->dataSize; i++){
            this->data.append(QRandomGenerator::global()->generateDouble());
        }
    }




private:

    void addUser(UserEquipment user){
        this->currentUsers.push_back(user);
    }

    void initialParameters(){
        this->PCI = 123;
        this->TxPower = 43;
        this->antennaGain = 18;
        this->otherLosses = 0;
        this->noiseFigure = 3;
        this->reqSINR = -3.3;
        this->bandwidth = 10;
        calculateThermalNoise(this->bandwidth);
        this->RxSensitivity = this->thermalNoise + this->noiseFigure + this->reqSINR;
    }
};


#endif // BASESTATION_H
