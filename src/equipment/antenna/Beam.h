#pragma once

#include <QVector>

class Bandwidth;

class Beam
{
public:
    float _absoluteAzimuthAngle;
    float _absoluteElevationAngle;
    float _beamWidth;
    float _gain = 18;

    QVector< Bandwidth* > _bandwidthContainer;

public:
    Beam();
    Beam(float azimuth, float elevation, float beamWidth);

    void config(float azimuth, float elevation, float beamWidth);
    void defaultGain(float gain);
    float calculateAntGain(float elevation, float azimuth);
    float calculateVerticalCutGain(float elevation);
    float calculateHorizontalCutGain(float azimuth);

    QVector<Bandwidth*> &getBandwidthContainer();

    void configNewBandwidth(QString fr, QString band, int scs, bool cpType, double ulBw,
                            double dlBw, int ulOffset, int dlOffset, bool tddTrue, int mimoIndex);
    void addBandwidth(Bandwidth *b);
};

