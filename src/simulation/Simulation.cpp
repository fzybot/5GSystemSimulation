#include "Simulation.h"
//#include "src/channel/propagation_models.h"

#include <cmath>

#include <QRandomGenerator>
#include <QDebug>
#include <QtMath>
#include <QtWidgets>


Simulation::Simulation()
{
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
//void Simulation::generategNodeBs(int numberOfBaseStations){
//    // Generate random position
//    QRandomGenerator gen1 =  QRandomGenerator();
//    for(int i = 0; i < numberOfBaseStations; i ++){
//        double randomLon = this->minLon + gen1.bounded(this->maxLon - this->minLon);
//        double randomLat = this->minLat + gen1.bounded(this->maxLat - this->minLat);
//        gNodeB tempBaseStation;
//        tempBaseStation.ID = 100 + i;
//        tempBaseStation.assignLonLat(randomLon, randomLat, 0);
//        this->baseStations.push_back(tempBaseStation);
//    }
//}

//void Simulation::generateUEs(int numberOfUEs){
//    // Generate random position
//    QRandomGenerator gen2 =  QRandomGenerator();
//    for(int i = 0; i < numberOfUEs; i ++){
//        double randomLon = this->minLon + gen2.bounded(this->maxLon - this->minLon);
//        double randomLat = this->minLat + gen2.bounded(this->maxLat - this->minLat);
//        UserEquipment tempUser;
//        tempUser.identity = i + 10000;
//        tempUser.assignLonLat(randomLon, randomLat, 0);
//        tempUser.speed = gen2.bounded(0, 50);
//        tempUser.calculateStepSize();
//        this->userEqipmnets.push_back(tempUser);
//    }
//}

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
        if (distance == 0){
            return 30;
        }
        else{
            return 36.7 * log10(distance) + 26 * log10(2.6) + 22.7;
        }
    }
}

//void Simulation::calculateSINR(){
//    for (int ues = 0; ues < this->userEqipmnets.length(); ues++){
//        double S = -1000000;
//        double I = userEqipmnets[ues].thermalNoise;
//        double d = 0;
//        double L = 0;
//        for(int bs = 0; bs < this->baseStations.length(); bs++){
//            d = calculateDistance(this->userEqipmnets[ues].longtitude,
//                                  this->userEqipmnets[ues].latitude,
//                                  this->baseStations[bs].longtitude,
//                                  this->baseStations[bs].latitude);
//            L = -1 * calculatePathLoss(d, 0) + this->baseStations[bs].EIRP;
//            if(L > -140){
//                if (L >= S){
//                    S = L;
//                }
//                I = I + log2(1+pow(2, (L-I)/3));
//            }
//        }
//        for(int ue = 0; ue< this->userEqipmnets.length();ue++){
//            if (ue != ues){
//                d = calculateDistance(this->userEqipmnets[ues].longtitude,
//                                      this->userEqipmnets[ues].latitude,
//                                      this->userEqipmnets[ue].longtitude,
//                                      this->userEqipmnets[ue].latitude);
//                L = -1 * calculatePathLoss(d, 0) + this->userEqipmnets[ue].EIRP;
//                if(L > -140){
//                    I = I + log2(1+pow(2, (L-I)/3));
//                }
//            }
//        }
//        userEqipmnets[ues].SINR = S - I;
//        qDebug() << "UE SINR: "<< userEqipmnets[ues].SINR;
//    }
//}








//void Simulation::printUEs(){
//    qDebug() << this->userEqipmnets;
//}

//void Simulation::printBSs(){
//    qDebug() << this->baseStations;
//}
