#include <QVector>
#include <QtMath>

#include "Beam.h"

Beam::Beam()
{

}

Beam::Beam(float azimuth, float elevation, float beamWidth)
{
    _absoluteAzimuthAngle = azimuth;
    _absoluteElevationAngle = elevation;
}

float Beam::calculateAntGain(float elevation, float azimuth)
{
    _gain = (-1) * qMin(   (-1) * calculateVerticalCutGain(elevation) + calculateHorizontalCutGain(azimuth), 
                                static_cast<float>(30));
    return _gain;
}

float Beam::calculateVerticalCutGain(float elevation)
{
    float gain;
    float pow_ = 12*qPow(static_cast<float>(static_cast<float>(elevation - 90.0) / 65.0), 2);
    gain = (-1)*qMin(pow_, static_cast<float>(30));
    return gain;
}

float Beam::calculateHorizontalCutGain(float azimuth)
{
    float gain;

    float pow_ = 12*qPow(static_cast<float>(static_cast<float>(azimuth/65)), 2);
    gain = (-1)*qMin(pow_, static_cast<float>(30));

    return gain;
}

void Beam::defaultGain(double gain)
{
    _gain = gain;
}
