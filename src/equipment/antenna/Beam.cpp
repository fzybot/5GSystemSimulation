#include <QVector>
#include <QtMath>
#include <QDebug>

#include "Beam.h"
#include "src/protocols/phy/Bandwidth.h"

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
    qDebug() << "Absolute azimuth: " << _absoluteAzimuthAngle;
    qDebug() << "Elevation: " << _absoluteElevationAngle;
    qDebug() << "Beam width: " << _beamWidth;
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

void Beam::configNewBandwidth(QString fr, QString band, int scs, bool cpType, double ulBw,
                        double dlBw, int ulOffset, int dlOffset, bool tddTrue, int mimoIndex)
{
    //QString fr, QString band, int scs, double ulBw, double dlBw, int ulOffset, int dlOffset, bool tddTrue = true
    qDebug() << "Create new bandwidth...";
    Bandwidth *bw = new Bandwidth(fr, band, scs, cpType, ulBw, dlBw, ulOffset, dlOffset, mimoIndex, 0, tddTrue);
    bw->setCoreset({0, 1}, bw->getNumberOfPRB() - 20, 1);
    bw->setDmrs(1, 3, 1, 3);
    bw->configResourceGrid();
    bw->fillIndexes();
    addBandwidth(bw);
}

void Beam::addBandwidth(Bandwidth *b)
{
    _bandwidthContainer.push_back(b);
}

QVector< Bandwidth* > &Beam::getBandwidthContainer()
{
    return _bandwidthContainer;
}
