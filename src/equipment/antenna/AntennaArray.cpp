#include "AntennaArray.h"

AntennaArray::AntennaArray()
{

}

AntennaArray::AntennaArray(int sizeX, int sizeY)
{
    sizeX_ = sizeX;
    sizeY_ = sizeY;
}

void AntennaArray::addAntenna(Antenna *ant)
{
    antennaArray_.append(ant);
}
