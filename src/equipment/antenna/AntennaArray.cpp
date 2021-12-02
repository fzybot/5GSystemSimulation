#include "AntennaArray.h"

#include <QDebug>
#include <QtMath>

AntennaArray::AntennaArray()
{

}

float AntennaArray::calculateElevation(float angle)
{
    elevation_ = (angle * M_PI) / 180;
    return elevation_;
}
float AntennaArray::calculateAzimuth(float angle)
{
    azimuth_ = (angle * M_PI) / 180;
    return azimuth_;
}

float AntennaArray::getElevation(float angle)
{
    return elevation_;
}
float AntennaArray::getAzimuth(float angle)
{
    return azimuth_;
}

void AntennaArray::calculateElevationGrid()
{
    for (int i = -90; i <= 90; i++){
        elevationGrid_.append(calculateElevation(i));
    }
}
void AntennaArray::calculateAzimuthGrid()
{
    for (int i = -180; i <= 190; i++){
        azimuthGrid_.append(calculateAzimuth(i));
    }
}

QVector<float> &AntennaArray::getElevationGrid()
{
    return elevationGrid_;
}
QVector<float> &AntennaArray::getAzimuthGrid()
{
    return azimuthGrid_;
}



void AntennaArray::showElevationGrid()
{
    for(auto i : getElevationGrid())
        qDebug() << "Elevation Grid: " << i;
}
void AntennaArray::showAzimuthGrid()
{
    for(auto i : getAzimuthGrid())
        qDebug() << "Azimuth Grid: " << i;
}
