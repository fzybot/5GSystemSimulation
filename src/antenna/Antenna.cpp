#include "Antenna.h"


Antenna::Antenna(int gain, int type) :
    gain(gain),
    type(type)
{ }

void Antenna::setGain(int gain)
{
    this->gain = gain;
}
