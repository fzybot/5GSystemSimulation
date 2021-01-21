#include "simulation.h"
#include <QRandomGenerator>

Simulation::Simulation()
{
    calculateCoordinateBordersFromPixel();
    generateBaseStations(21);
    generateUEs(1000);
}

void Simulation::setSimulationTime(int time)
{
    this->simulationTime = time;
}

void Simulation::setCoordinateBorders(double MAXLAT, double MAXLON, double MINLAT, double MINLON,
                                        double MINALT, double MAXALT){
    this->maxLat = MAXLAT;
    this->maxLon = MAXLON;
    this->maxAlt = MAXALT;
    this->minLat = MINLAT;
    this->minLon = MINLON;
    this->minAlt = MINALT;
}

void Simulation::calculateCoordinateBordersFromPixel(){

    double meterSize = 0.00001;

    // if minLat and minLon are known then calculate a Pixel and Lat Lon borders
    if(this->maxPixelX > 0 && this->maxPixelY > 0 && this->maxPixelZ > 0){
        this->maxLat = this->minLat + (meterSize * maxPixelY);
        this->maxLon = this->minLon + (meterSize * maxPixelX);
    }
}

double Simulation::pixelToll(int x, int y, double minLon, double minLat, double maxLon,
                             double maxLat){
    // x is lon, y is lat
    double deltaLon = maxLon - minLon;
    double deltaLat = maxLat - minLon;
    double xFrac = x / this->maxPixelX;
    double yFrac = y / this->maxPixelY;

    //lon = minLon -

    return 0;
}

int Simulation::llToPixel(double lon, double lat){


    return 0;
}



void Simulation::setPixelBorders(int maxX, int maxY, int minX, int minY, int maxZ, int minZ){
    this->maxPixelX = maxX;
    this->maxPixelY = maxY;
    this->minPixelX = minX;
    this->minPixelY = minY;
    this->maxPixelZ = maxZ;
    this->minPixelZ = minZ;
}

void Simulation::generateBaseStations(int numberOfBaseStations){
    // Generate random position
    for(int i = 0; i < numberOfBaseStations; i ++){
        int randomPixelX = QRandomGenerator::global()->bounded(this->minPixelX, this->maxPixelX);
        int randomPixelY = QRandomGenerator::global()->bounded(this->minPixelY, this->maxPixelY);
        BaseStation tempBaseStation;
        tempBaseStation.cellIdentity = 100 + i;
        tempBaseStation.assignPixelCoordinates(randomPixelX, randomPixelY, 0);
        this->baseStations.push_back(tempBaseStation);
    }
}

void Simulation::generateUEs(int numberOfUEs){
    // Generate random position
    for(int i = 0; i < numberOfUEs; i ++){
        int randomPixelX = QRandomGenerator::global()->bounded(this->minPixelX, this->maxPixelX);
        int randomPixelY = QRandomGenerator::global()->bounded(this->minPixelY, this->maxPixelY);
        UserEquipment tempUser;
        tempUser.identity = i + 10000;
        tempUser.assignPixelCoordinates(randomPixelX, randomPixelY, 0);
        this->userEqipmnets.push_back(tempUser);
    }
}

void Simulation::generateNoise(int size){
    for (int i = 0; i < size; i++){
        this->noise.append(QRandomGenerator::global()->generateDouble() / 100);
    }
}

void Simulation::showBordersll(){
    qDebug() << "Lat Lon borders:" << Qt::endl;
    qDebug() << this->maxLat << this->maxLon << this->minLat << this->minLon;
}

//void Simulation::printUEs(){
//    qDebug() << this->userEqipmnets;
//}

//void Simulation::printBSs(){
//    qDebug() << this->baseStations;
//}
