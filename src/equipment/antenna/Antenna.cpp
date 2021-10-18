#include "Antenna.h"

Antenna::Antenna()
{

}

Antenna::Antenna(int posX, int posY)
{
    setPosition(posX, posY);
}

Antenna::Antenna(int posX, int posY, Antenna::AntennaType type)
{
    setPosition(posX, posY);
    setAntennaType(type);
}

void Antenna::setPosition(int posX, int posY)
{
    positionX_ = posX;
    positionY_ = posY;
}

void Antenna::setAntennaType(Antenna::AntennaType type)
{
    type_ = type;
}
Antenna::AntennaType Antenna::getAntennaType()
{
    return type_;
}

float Antenna::calcRadiationPattern(float angle, float absoluteAngle)
{
    // TODO: need to calculate Radiation Pattern
    return 1;
}
