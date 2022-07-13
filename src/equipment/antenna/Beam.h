#pragma once


class Beam
{
public:
    float _absoluteAzimuthAngle;
    float _absoluteElevationAngle;
    double _gain = 0;

public:
    Beam();
    Beam(float azimuth, float elevation, float beamWidth);

    void defaultGain(double gain);
    float calculateAntGain(float elevation, float azimuth);
    float calculateVerticalCutGain(float elevation);
    float calculateHorizontalCutGain(float azimuth);
};

