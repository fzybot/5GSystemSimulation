#pragma once


class Beam
{
public:
    float _absoluteAzimuthAngle;
    float _absoluteElevationAngle;
    float _beamWidth;
    float _gain = 18;

public:
    Beam();
    Beam(float azimuth, float elevation, float beamWidth);

    void config(float azimuth, float elevation, float beamWidth);
    void defaultGain(float gain);
    float calculateAntGain(float elevation, float azimuth);
    float calculateVerticalCutGain(float elevation);
    float calculateHorizontalCutGain(float azimuth);
};

