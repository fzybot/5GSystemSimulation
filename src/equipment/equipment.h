#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QVector>
#include <QDebug>
#include <math.h>

#include <src/common_parameters.h>

class Equipment {

public:

    /* Coordinates & Geometry for spherical basis
     * According to 3GPP TS38.901:
     *  latitude is 'y' axis
     *  lontitude is 'x' axis
     *  altitude is  'z' axis (height above the sea)
     *
     *  angles:
     *      lonAngle - 'fi'
     *      latAngle - '0'
     *  variables: pixelX, pixelY, pixelZ is used to draw an image
     *  There are functions to transform pixel into latlon and inverse
     */

    double altitude = 0;
    double longtitude;
    double latitude;

    int pixelX;
    int pixelY;
    int pixelZ;

    double lonAngle = 0;
    double latAngle = 0;

    double height;




    // Link budget parameters
    double TxPower;
    double feederLoss;
    int bodyLosses = 3;
    int antennaGain;
    double otherGain = 0;
    double otherLosses = 0;
    double otherMargins = 0;
    int noiseFigure;
    double thermalNoise;
    double reqSINR;
    double RxSensitivity;


    double pathLoss = 0; //to calculate


    // Frequency parameters
    int ARFCN = 0;
    int numerologyIndex = 0;
    int SCS = NUMEROLOGY[numerologyIndex];
    int bandwidth;
    int carrierFrequency; // in Mhz


    //
    int mimoLayers = 1;
    QVector<double> data;
    QVector<double> dataPlusInterference; //TODO: generate phase and amplitude interference
    QVector<double> dataEnergy; // according to MAPL
    QVector<double> dataEnergyPlusInterference; // according to all neighbour (gNb + UE) MAPL
    int dataSize;





public:
    Equipment(){

    }

    void printData(){
        qDebug() << this->data;
    }

    void calculateThermalNoise(int bandwidth){
        this->thermalNoise = -174 + 10 * log10(bandwidth * 1000000);
    }

    void assignLatLon(double lon, double lat, double alt){
        this->latitude = lat;
        this->longtitude = lon;
        this->altitude = alt;
    }

    void generateRandomCoordinates(double minLon, double minLat, double maxLon, double maxLat,
                                   double minAlt, double maxAlt){


    }

    void assignPixelCoordinates(int x, int y, int z){
        this->pixelX = x;
        this->pixelY = y;
        this->pixelZ = z;
    }



};

#endif // EQUIPMENT_H
