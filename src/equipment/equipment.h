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
    QVector<float> data;
    QVector<float> dataEnergy;
    int dataSize;





public:
    Equipment(){
        this->bandwidth = 10;
        this->dataSize = ( ((this->bandwidth * 1000) / this->SCS ) * 2 * 14 );
        calculateThermalNoise(this->bandwidth);
    }

    void setPixelCoordinates(int x, int y, int z){
        this->pixelX = x;
        this->pixelY = y;
        this->pixelZ = z;
    }
    void setLatitude(double lat){
        this->latitude = lat;
    }

    void setLontitude(double lon){
        this->longtitude = lon;
    }

    void setAltitude(double alt){
        this->altitude = alt;
    }

    void printData(){
        qDebug() << this->data;
    }

    void calculateThermalNoise(int bandwidth){
        this->thermalNoise = -174 + 10 * log10(bandwidth * 1000000);
    }

};

#endif // EQUIPMENT_H
