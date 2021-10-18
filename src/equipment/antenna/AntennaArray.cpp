#include "AntennaArray.h"
#include "src/equipment/antenna/Antenna.h"

AntennaArray::AntennaArray()
{

}

AntennaArray::AntennaArray(int sizeX, int sizeY)
{
    setSize(sizeX, sizeY);
    for (int x = 0; x < sizeX_; x++) {
        for (int y = 0; y < sizeY_; y++) {
            Antenna ant(x, y, Antenna::AntennaType::ANTENNA_TYPE_OMNIDIRECTIONAL);
            addAntenna(ant);
        }
    }
}

void AntennaArray::setSize(int sizeX, int sizeY)
{
    sizeX_ = sizeX;
    sizeY_ = sizeY;
}

void AntennaArray::addAntenna(Antenna ant)
{
    antennaArray_.push_back(ant);
}

QVector<Antenna> &AntennaArray::getAntennaArray()
{
    return antennaArray_;
}
