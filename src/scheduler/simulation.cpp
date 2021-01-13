#include "simulation.h"
#include <QRandomGenerator>

Simulation::Simulation()
{
    generateBaseStations(21);
    generateUEs(1000);
}

void Simulation::setUpSimulationTime(int time)
{
    this->simulationTime = time;
}

void Simulation::setUpCoordinateBorders(double MAXLAT, double MAXLON, double MINLAT, double MINLON,
                                        double MINALT, double MAXALT){
    this->maxLat = MAXLAT;
    this->maxLon = MAXLON;
    this->maxAlt = MAXALT;
    this->minLat = MINLAT;
    this->minLon = MINLON;
    this->minAlt = MINALT;
}

void Simulation::setUpPixelBorders(int maxX, int maxY, int minX, int minY, int maxZ, int minZ){
    this->maxPixelX = maxX;
    this->maxPixelY = maxY;
    this->minPixelX = minX;
    this->minPixelY = minY;
    this->maxPixelZ = maxZ;
    this->minPixelZ = maxZ;
}

void Simulation::generateBaseStations(int numberOfBaseStations){
    // Generate random position
    for(int i = 0; i < numberOfBaseStations; i ++){
        int randomPixelX = QRandomGenerator::global()->bounded(this->minPixelX, this->maxPixelX);
        int randomPixelY = QRandomGenerator::global()->bounded(this->minPixelY, this->maxPixelY);
        BaseStation tempBaseStation;
        tempBaseStation.cellIdentity = i;
        tempBaseStation.setPixelCoordinates(randomPixelX, randomPixelY, 0);
        this->baseStations.push_back(tempBaseStation);
    }
}

void Simulation::generateUEs(int numberOfUEs){
    // Generate random position
    for(int i = 0; i < numberOfUEs; i ++){
        int randomPixelX = QRandomGenerator::global()->bounded(this->minPixelX, this->maxPixelX);
        int randomPixelY = QRandomGenerator::global()->bounded(this->minPixelY, this->maxPixelY);
        UserEquipment tempUser;
        tempUser.identity = i + 1000;
        tempUser.setPixelCoordinates(randomPixelX, randomPixelY, 0);
        this->userEqipmnets.push_back(tempUser);
    }
}

void Simulation::generateNoise(int size){
    for (int i = 0; i < size; i++){
        this->noise.append(QRandomGenerator::global()->generateDouble() / 100);
    }
}

//void Simulation::printUEs(){
//    qDebug() << this->userEqipmnets;
//}

//void Simulation::printBSs(){
//    qDebug() << this->baseStations;
//}
