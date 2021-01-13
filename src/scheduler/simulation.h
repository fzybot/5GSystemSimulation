#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QVector>
#include <QDebug>

#include <src/equipment/user_equipment.h>
#include <src/equipment/base_station.h>

class Simulation: public QObject
{
    Q_OBJECT

public:

    int simulationTime = 1000; // [slots]

    // map borders
    // up = 55.016656, 82.942833     down = 55.012888, 82.952097      center = 55.014619, 82.946997
    double maxLat;
    double maxLon;
    double maxAlt;
    double minLat;
    double minLon;
    double minAlt;
    // Novosibirsk
    double centerLat = 55.014619;
    double centerLon = 82.946997;
    double centerAlt = 0;

    // coordinate system in pixels to draw an image
    int maxPixelX = 15000;
    int maxPixelY = 15000;
    int maxPixelZ = 120;
    int minPixelX = 0;
    int minPixelY = 0;
    int minPixelZ = 0;
    int onePixelDistance = 3; //[meters]

    QVector<UserEquipment> userEqipmnets;
    QVector<BaseStation> baseStations;

    QVector<float> noise;




public:
    Simulation();
    void start();
    void configurate();


private:
    void setUpSimulationTime(int time); // in [TTIs, slots]
    void setUpCoordinateBorders(double MAXLAT, double MAXLON, double MINLAT, double MINLON,
                                double MINALT, double MAXALT);
    void setUpPixelBorders(int maxX, int maxY, int minX, int minY, int maxZ, int minZ);
    void generateBaseStations(int numberOfBaseStations);
    void generateUEs(int numberOfUEs);
    void generateNoise(int size);
    void pixelToll();
    void lltoPixel();
};

#endif // SIMULATION_H
