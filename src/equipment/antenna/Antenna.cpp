#include "Antenna.h"

Antenna::Antenna()
{

}


Antenna::Antenna(int posX, int posY)
{
    setPosition(posX, posY);
}

void Antenna::setPosition(int posX, int posY)
{
    positionX_ = posX;
    positionY_ = posY;
}
