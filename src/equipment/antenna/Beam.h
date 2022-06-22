#pragma once


class Beam
{
public:
    float _absoluteAzimuthAngle;
    float _absoluteElevationAngle;
public:
    Beam();
    Beam(float azimuth, float elevation, float beamWidth);

    float calculateAntGain(float elevation, float azimuth);
    float calculateVerticalCutGain(float elevation);
    float calculateHorizontalCutGain(float azimuth);
};

