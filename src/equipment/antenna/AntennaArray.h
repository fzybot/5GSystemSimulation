#pragma once

#include "src/equipment/antenna/Antenna.h"

#include <QVector>


class Antenna;


class AntennaArray
{
private:
    // The number of antennas inside array.
    int sizeX_;
    int sizeY_;

    QVector<Antenna> antennaArray_;

public:
    AntennaArray();
    AntennaArray(int sizeX = 1, int sizeY = 1);

    void setSize(int sizeX, int sizeY);

    void addAntenna(Antenna ant);
    Antenna* getAntennaByID(int ID);

};

