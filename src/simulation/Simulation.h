#pragma once


#include <QObject>
#include <QVector>
#include <QDebug>

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"


class Simulation: public QObject
{
    Q_OBJECT

public:
    int simulationTime = 1000; // [slots]
    int scenario = 0;

    // map borders
    // up = 55.016656, 82.942833     down = 55.012888, 82.952097      center = 55.014619, 82.946997
    // Novosibirsk
    double maxLat;
    double maxLon;
    double maxAlt;
    double minLat = 55.014619;
    double minLon = 82.946997;
    double minAlt = 0;

    double centerLat;
    double centerLon;
    double centerAlt;

    // coordinate system in pixels to draw an image
    int maxPixelX = 1500;
    int maxPixelY = 1500;
    int maxPixelZ = 120;
    int minPixelX = 0;
    int minPixelY = 0;
    int minPixelZ = 0;
    int onePixelDistance = 1; //[meters]

    QVector<UserEquipment> userEqipmnets;
    QVector<gNodeB> baseStations;
    QVector<float> noise;

public:
    Simulation();

    void runSingleSimulation();
    void runMultipleSimulation();
    void configurate();
    void showBordersll();

    double mWattTodBm(double mWatts);
    double dBmTomWatt(double dBm);

    void calculateSINR();
    double calculatePathLoss(double distance, double angle);

private:
    void setSimulationTime(int time); // in [TTIs, slots]
    void setCoordinateBorders(double MAXLAT, double MAXLON, double MINLAT, double MINLON,
                                double MINALT, double MAXALT);
    void calculateCoordinateBordersFromPixel();
    void setPixelBorders(int maxX, int maxY, int minX, int minY, int maxZ, int minZ);
    double pixelToll(int x, int y, double minLon, double minLat, double maxLon, double maxLat);
    int llToPixel(double lon, double lat);
    double calculateDistance(double lon1, double lat1, double lon2, double lat2);

    void generategNodeBs(int numberOfBaseStations);
    void generateUEs(int numberOfUEs);
    void updateNeighbours();
    void generateNoise(int size);
};
