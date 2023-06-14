#include <QVector>
#include <QtMath>

#include "Beam.h"

Beam::Beam()
{

}
Beam::Beam(float azimuth, float elevation, float beamWidth)
{
    config(azimuth, elevation, beamWidth);
}

void Beam::config(float azimuth, float elevation, float beamWidth)
{
    _absoluteAzimuthAngle = azimuth;
    _absoluteElevationAngle = elevation;
    _beamWidth = beamWidth;
}
float Beam::calculateAntGain(float elevation, float azimuth)
{
    float gain = (-1) * qMin(   (-1) * calculateVerticalCutGain(elevation) + calculateHorizontalCutGain(azimuth),
                                static_cast<float>(30));
    return _gain + gain;
}

float Beam::calculateVerticalCutGain(float elevation)
{
    float gain;
    float pow_ = 12*qPow(static_cast<float>(static_cast<float>((_absoluteElevationAngle + elevation) - 90.0) / 65.0), 2);
    gain = (-1)*qMin(pow_, static_cast<float>(30));
    return gain;
}

float Beam::calculateHorizontalCutGain(float azimuth)
{
    float gain;

    float pow_ = 12*qPow(static_cast<float>(static_cast<float>((_absoluteAzimuthAngle + azimuth) / 125)), 2);
    gain = (-1)*qMin(pow_, static_cast<float>(30));

    return gain;
}

void Beam::defaultGain(float gain)
{
    _gain = gain;
}
