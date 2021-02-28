#include "simulation.h"
#include <cmath>
#include <QRandomGenerator>
#include <QDebug>

//#include <src/channel/propagation_models.h>

Simulation::Simulation()
{
    calculateCoordinateBordersFromPixel();
    generateBaseStations(5);
    generateUEs(30);
    setSimulationTime(100);
    calculateSINR();
    qDebug() << "dBm: "<< mWattTodBm(20000);
    qDebug() << "mWatt: "<< dBmTomWatt(43);

}

void Simulation::runSingleSimulation(){

    // Simulation is started
    for (int slot = 0; slot < this->simulationTime; slot++ ){

    }
}

//**************************************************************
// Configuration methods
//**************************************************************
void Simulation::setSimulationTime(int time)
{
    this->simulationTime = time;
}

//**************************************************************
// LOGISTIC METHODS
//**************************************************************
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

void Simulation::showBordersll(){
    qDebug() << "Lat Lon borders:" << Qt::endl;
    qDebug() << this->maxLat << this->maxLon << this->minLat << this->minLon;
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

// in [meters]
double Simulation::calculateDistance(double lon1, double lat1, double lon2, double lat2){
    double pi = 3.141592;
    double a, c;
    int R = 6371210; // Earth radius
    // into radians
    double dLon = (lon2  - lon1) * (pi / 180);
    double dLat = (lat2  - lat1) * (pi / 180);

    a = sin(dLon / 2) * sin(dLon / 2) + cos(lon1 * (pi / 180)) * cos(lon2 * (pi / 180)) *
            sin(dLat / 2) * sin(dLat / 2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

//**************************************************************
// UE and BS Generation methods
//**************************************************************
void Simulation::generateBaseStations(int numberOfBaseStations){
    // Generate random position
    QRandomGenerator gen1 =  QRandomGenerator();
    for(int i = 0; i < numberOfBaseStations; i ++){
//        int randomPixelX = QRandomGenerator::global()->bounded(this->minPixelX, this->maxPixelX);
//        int randomPixelY = QRandomGenerator::global()->bounded(this->minPixelY, this->maxPixelY);
        double randomLon = this->minLon + gen1.bounded(this->maxLon - this->minLon);
        double randomLat = this->minLat + gen1.bounded(this->maxLat - this->minLat);
        BaseStation tempBaseStation;
        tempBaseStation.cellIdentity = 100 + i;
        tempBaseStation.assignLonLat(randomLon, randomLat, 0);
//        tempBaseStation.assignPixelCoordinates(randomPixelX, randomPixelY, 0);
        this->baseStations.push_back(tempBaseStation);
    }
}

void Simulation::generateUEs(int numberOfUEs){
    // Generate random position
    QRandomGenerator gen1 =  QRandomGenerator();
    for(int i = 0; i < numberOfUEs; i ++){
//        int randomPixelX = QRandomGenerator::global()->bounded(this->minPixelX, this->maxPixelX);
//        int randomPixelY = QRandomGenerator::global()->bounded(this->minPixelY, this->maxPixelY);
        double randomLon = this->minLon + gen1.bounded(this->maxLon - this->minLon);
        double randomLat = this->minLat + gen1.bounded(this->maxLat - this->minLat);
        UserEquipment tempUser;
        tempUser.identity = i + 10000;
        tempUser.assignLonLat(randomLon, randomLat, 0);
        tempUser.speed = gen1.bounded(0, 50);
        tempUser.calculateStepSize();
//        tempUser.assignPixelCoordinates(randomPixelX, randomPixelY, 0);
        this->userEqipmnets.push_back(tempUser);
    }
}

void Simulation::updateNeighbours(){

}


//**************************************************************
// Physical effects methods
//**************************************************************

double Simulation::mWattTodBm(double mWatts){

    return 10 * log10(mWatts);
}

double Simulation::dBmTomWatt(double dBm){
    return pow(10, dBm/10);
}

void Simulation::generateNoise(int size){
    for (int i = 0; i < size; i++){
        this->noise.append(QRandomGenerator::global()->generateDouble() / 100);
    }
}

double Simulation::calculatePathLoss(double distance, double angle){
    if (this->scenario == 0){
        return 36.7 * log10(distance) + 26 * log10(2.6) + 22.7;
    }
}

void Simulation::calculateSINR(){
    double S = -1000000;
    double I = userEqipmnets[0].thermalNoise;
    double d = 0;
    double L = 0;
    for(int bs = 0; bs < this->baseStations.length(); bs++){
        d = calculateDistance(this->userEqipmnets[0].longtitude, this->userEqipmnets[0].latitude,
                this->baseStations[bs].longtitude, this->baseStations[bs].latitude);
        L = -1 * calculatePathLoss(d, 0) + this->baseStations[bs].EIRP;
        if(L > -140){
            if (L >= S){
                S = L;
            }
            //I = I + log2(1+pow(2, (L-I)/3));
            I = I + L;
            qDebug() << "BS PL: "<< L << "Interf: " << I;
            qDebug() << "   BS Distance: "<< d;
        }
    }
    for(int ue = 1; ue< this->userEqipmnets.length();ue++){
        d = calculateDistance(this->userEqipmnets[0].longtitude, this->userEqipmnets[0].latitude,
                this->userEqipmnets[ue].longtitude, this->userEqipmnets[ue].latitude);
        L = -1 * calculatePathLoss(d, 0) + this->userEqipmnets[ue].EIRP;
        if(L > -140){
            I = I + log2(1+pow(2, (L-I)/3));
            qDebug() << "UE PL: "<< L << "Interf: " << I;
        }
    }
    qDebug() << "S: "<< mWattTodBm(S);
    qDebug() << "I: "<< mWattTodBm(I);
    //userEqipmnets[0].SINR = (S/ (I + N));
}








//void Simulation::printUEs(){
//    qDebug() << this->userEqipmnets;
//}

//void Simulation::printBSs(){
//    qDebug() << this->baseStations;
//}
