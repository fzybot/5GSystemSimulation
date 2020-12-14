#ifndef SIMULATION_H
#define SIMULATION_H
#include <QObject>

class Simulation: public QObject
{
    Q_OBJECT

public:

    int simulationTime = 1000; // [TTIs]

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
    int maxPixelX = 5000;
    int maxPixelY = 5000;
    int maxPixelZ = 120;
    int minPixelX = 0;
    int minPixelY = 0;
    int minPixelZ = 0;
    int onePixelDistance = 3; //[meters]




public:
    Simulation();
    void start();
    void configurate();


private:
    void setUpSimulationTime(int time); // in [TTIs]
    void setUpCoordinateBorders(double MAXLAT, double MAXLON, double MINLAT, double MINLON,
                                double MINALT, double MAXALT);
    void generateBaseStations(int numberOfBaseStations);
    void generateUEs(int numberOfUEs);
    void pixelToll();
    void lltoPixel();
};

#endif // SIMULATION_H
