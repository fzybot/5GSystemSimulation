#include "AntennaArray.h"

#include <QDebug>
#include <QtMath>
#include <QtDataVisualization/Q3DSurface>
#include <QtWidgets>
#include "src/visualization/Custom3dSurface.h"

#include "src/equipment/antenna/Beam.h"

AntennaArray::AntennaArray()
{

}

AntennaArray::AntennaArray(AntennaArray::AntennaType type, int sizeX, int sizeY, 
                            float azimuth, float elevation, float beamWidth, float sectorWidth)
{
    setAntennaType(type);
    switch (type)
    {
        case AntennaArray::AntennaType::ANTENNA_TYPE_OMNIDIRECTIONAL:
            setDefaultGain(0);
            configAntennaGrid(sizeX, sizeY);
            setBeams(azimuth, elevation, beamWidth, sectorWidth);
            break;
        case AntennaArray::AntennaType::ANTENNA_TYPE_3GPP_CUSTOM:
            setDefaultGain(12);
            configAntennaGrid(sizeX, sizeY);
            setBeams(azimuth, elevation, beamWidth, sectorWidth);
            break;
    }
}

void AntennaArray::configAntennaGrid(int sizeX, int sizeY)
{
    _beamContainer.resize(sizeX);
    for (int i = 0; i < _beamContainer.size(); i++){
        _beamContainer[i].resize(sizeY);
    }
    qDebug() << _beamContainer;
}

void AntennaArray::setBeams(float azimuth, float elevation, float beamWidth, float sectorWidth)
{   
    _absoluteAzimuthAngle = azimuth;
    _absoluteElevationAngle = elevation;

    for (int i = 0; i < _beamContainer.size(); i++){
        for (int j = 0; j < _beamContainer[0].size(); j++){
            qDebug() << "Beam config: [" << i << ", " << j << "]";
            float dAzim = (_absoluteAzimuthAngle - sectorWidth / 2) + beamWidth / 2;
            Beam *beam = new Beam(_absoluteAzimuthAngle + (j * (beamWidth / 2) ), _absoluteElevationAngle, beamWidth);
            //Beam *beam = new Beam(_absoluteAzimuthAngle + (i * (sectorWidth / 2) ), _absoluteElevationAngle, beamWidth);
            _beamContainer[i][j] = beam;
        }
    }
}

void AntennaArray::setAntennaType(AntennaArray::AntennaType type)
{
    _type = type;
}

AntennaArray::AntennaType &AntennaArray::getAntennaType()
{
    return _type;
}

QVector<QVector<Beam *>> &AntennaArray::getBeamContainer()
{
    return _beamContainer;
}

float AntennaArray::gainPerBeamIndex(int indexX, int indexY, int elevation, int azimuth)
{
    return _beamContainer[indexX][indexY]->calculateAntGain(elevation, azimuth);
}

void AntennaArray::setDefaultGain(double gain)
{
    for (int i = 0; i < _beamContainer.length(); i++){
        for (int j = 0; j < _beamContainer[0].length(); j++){
            _beamContainer[i][j]->defaultGain(gain);
        }
    }
}

// void AntennaArray::setAntennaType(AntennaType type)
// {
//     type_ = type;
// }
// AntennaArray::AntennaType AntennaArray::getAntennaType()
// {
//     return type_;
// }

// float AntennaArray::calculateElevation(float angle)
// {
//     elevation_ = (angle * M_PI) / 180;
//     return elevation_;
// }
// float AntennaArray::calculateAzimuth(float angle)
// {
//     azimuth_ = (angle * M_PI) / 180;
//     return azimuth_;
// }

// float AntennaArray::getElevation(float angle)
// {
//     return elevation_;
// }
// float AntennaArray::getAzimuth(float angle)
// {
//     return azimuth_;
// }

// void AntennaArray::calculateElevationGrid()
// {
//     for (int i = -90; i <= 90; i++){
//         elevationGrid_.append(calculateElevation(i));
//     }
// }
// void AntennaArray::calculateAzimuthGrid()
// {
//     for (int i = -180; i <= 180; i++){
//         azimuthGrid_.append(calculateAzimuth(i));
//     }
// }

// QVector<float> &AntennaArray::getElevationGrid()
// {
//     return elevationGrid_;
// }
// QVector<float> &AntennaArray::getAzimuthGrid()
// {
//     return azimuthGrid_;
// }

// float AntennaArray::calculateAntGain(float elevation, float azimuth)
// {
//     float gain = (-1) * qMin(   (-1) * calculateVerticalCutGain(elevation) + calculateHorizontalCutGain(azimuth), 
//                                 static_cast<float>(30));
//     return gain;
// }

// float AntennaArray::calculateVerticalCutGain(float elevation)
// {
//     float gain;
//     float pow_ = 12*qPow(static_cast<float>(static_cast<float>(elevation - 90.0) / 65.0), 2);
//     gain = (-1)*qMin(pow_, static_cast<float>(30));
//     return gain;
// }

// float AntennaArray::calculateHorizontalCutGain(float azimuth)
// {
//     float gain;

//     float pow_ = 12*qPow(static_cast<float>(static_cast<float>(azimuth/65)), 2);
//     gain = (-1)*qMin(pow_, static_cast<float>(30));

//     return gain;
// }

// void AntennaArray::show3dPlot()
// {
//     calculateDataArray3d();
//     visualize3D();
// }

// void AntennaArray::show2dPlot()
// {
//     QVector<QPair<float, float>> test;
//     test.append(qMakePair(6, 6));
//     test.append(qMakePair(61, 61));
//     test.append(qMakePair(62, 63));
//     test.append(qMakePair(63, 65));

//     QVector<QVector<QPair<float, float>>> test1;
//     test1.append(test);
//     visualize2D(test1, "test");
// }

// void AntennaArray::calculateDataArray3d()
// {
//     int sampleCountZLocal = 90;
//     int sampleCountXLocal = 180;
//     dataArray3d_ = new QtDataVisualization::QSurfaceDataArray;
//     dataArray3d_->reserve(181);
//     for (int i = -90; i <= 90; i++) {
//         QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(361);
//         float z = i;
//         int index = 0;
//         for (int j = -180; j <= 180; j++) {
//             float x = j;
//             float y = calculateAntGain(i, j);
//             (*newRow)[index++].setPosition(QVector3D(x, y, z));
//         }
//         //qDebug() << "New row: " << newRow->size();
//         *dataArray3d_ << newRow;
//     }
// }

// void AntennaArray::showElevationGrid()
// {
//     for(auto i : getElevationGrid())
//         qDebug() << "Elevation Grid: " << i;
// }
// void AntennaArray::showAzimuthGrid()
// {
//     for(auto i : getAzimuthGrid())
//         qDebug() << "Azimuth Grid: " << i;
// }
