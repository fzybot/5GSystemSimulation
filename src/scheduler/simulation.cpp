#include "simulation.h"
#include <QRandomGenerator>

Simulation::Simulation()
{

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

void Simulation::generateUEs(int numberOfUEs){
    // Generate random position
    for(int i = 0; i < numberOfUEs; i ++){
        int randomPixelX = QRandomGenerator::global()->bounded(this->minPixelX, this->maxPixelX);
        int randomPixelY = QRandomGenerator::global()->bounded(this->minPixelY, this->maxPixelY);

    }

}
