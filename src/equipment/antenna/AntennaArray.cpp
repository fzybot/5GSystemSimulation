#include "AntennaArray.h"

#include <QDebug>
#include <QtMath>
#include <QtDataVisualization/Q3DSurface>
#include <QtWidgets>
#include "src/visualization/Custom3dSurface.h"

AntennaArray::AntennaArray()
{

}

void AntennaArray::setAntennaType(AntennaType type)
{
    type_ = type;
}
AntennaArray::AntennaType AntennaArray::getAntennaType()
{
    return type_;
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
    for (int i = -180; i <= 180; i++){
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

float AntennaArray::calculateAntGain(float elevation, float azimuth)
{
    float gain = (-1) * qMin(   (-1) * calculateVerticalCutGain(elevation) + calculateHorizontalCutGain(azimuth), 
                                static_cast<float>(30));
    return gain;
}

float AntennaArray::calculateVerticalCutGain(float elevation)
{
    float gain;
    float pow_ = 12*qPow(static_cast<float>(static_cast<float>(elevation - 90.0) / 65.0), 2);
    gain = (-1)*qMin(pow_, static_cast<float>(30));
    return gain;
}

float AntennaArray::calculateHorizontalCutGain(float azimuth)
{
    float gain;

    float pow_ = 12*qPow(static_cast<float>(static_cast<float>(azimuth/65)), 2);
    gain = (-1)*qMin(pow_, static_cast<float>(30));

    return gain;
}

void AntennaArray::calculateDataArray3d()
{
    int sampleCountZLocal = 90;
    int sampleCountXLocal = 180;
    dataArray3d_ = new QtDataVisualization::QSurfaceDataArray;
    dataArray3d_->reserve(181);
    for (int i = -90; i <= 90; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(361);
        float z = i;
        int index = 0;
        for (int j = -180; j <= 180; j++) {
            float x = j;
            float y = calculateAntGain(i, j);
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        //qDebug() << "New row: " << newRow->size();
        *dataArray3d_ << newRow;
    }
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
