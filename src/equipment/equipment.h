#pragma once


#include "src/commonParameters.h"

#include <math.h>

#include <QVector>
#include <QDebug>
#include <QGraphicsItem>


class Equipment
{
public:
    /*
     * Coordinates & Geometry for spherical basis
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
    double altAngle = 0;

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

    double EIRP;

    double pathLoss = 0; //to calculate

    // Frequency parameters
    int ARFCN = 0;
    int carrierFrequency = 2600; // [MHz]
    int numerologyIndex = 0;
    int SCS = NUMEROLOGY[numerologyIndex];
    int bandwidth;

    // SINR
    double SINR = 0;

    // Data array before FFT
    int mimoLayers = 1;
    QVector<double> data;
    QVector<double> dataPlusDoppler;
    QVector<double> dataPlusInterference; //TODO: generate phase and amplitude interference
    QVector<double> dataEnergy; // according to MAPL
    QVector<double> dataEnergyPlusInterference; // according to all neighbour (gNb + UE) MAPL
    int dataSize;

    // Information about neighbour cells
    QVector<double> distanceToEachCell;

public:
    Equipment();

    void printData();

    void calculateThermalNoise();
    void calculateEIRP();
    void dopplerEffect(QVector<double> data, double speed, double angle);

    void assignLonLat(double lon, double lat, double alt);
    void generateRandomCoordinates(double minLon, double minLat, double maxLon, double maxLat, double minAlt, double maxAlt);
    void assignPixelCoordinates(int x, int y, int z);
};
