#pragma once

#include <QVector>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

#include "src/visualization/Chartable.h"


class Custom3dSurface;
class Beam;

class AntennaArray
{
// enum class AntennaType
//     {
//         ANTENNA_TYPE_OMNIDIRECTIONAL,
//         ANTENNA_TYPE_3GPP_3D,
//         ANTENNA_TYPE_3GPP_CUSTOM,
//     };
public:

    
    float _absoluteAzimuthAngle;
    float _absoluteElevationAngle;

    QVector<QVector<Beam*>> _beamContainer;

    //AntennaArray::AntennaType type_;  
    // float elevation_;
    // float azimuth_;
    // QVector<float> elevationGrid_;
    // QVector<float> azimuthGrid_;
    // QVector<QVector<float>> Fa_;
    // QVector<QVector<float>> Fb_;

public:
    AntennaArray();
    AntennaArray(int sizeX, int sizeY, float azimuth, float elevation, float beamWidth, float sectorWidth);

    void configAntennaGrid(int sizeX, int sizeY);
    void setBeams(float azimuth, float elevation, float beamWidth, float sectorWidth);

    // void setSize(int sizeX, int sizeY);
    // void setAntennaType(AntennaType type);
    // AntennaType getAntennaType();
    // float calculateElevation(float angle);   // range [-90:90]
    // float calculateAzimuth(float angle);     // range [-180:180]
    // float getElevation(float angle);
    // float getAzimuth(float angle);
    // void calculateElevationGrid();
    // void calculateAzimuthGrid();
    // QVector<float> &getElevationGrid();
    // QVector<float> &getAzimuthGrid();
    // float calculateAntGain(float elevation, float azimuth);
    // float calculateVerticalCutGain(float elevation);
    // float calculateHorizontalCutGain(float azimuth);
    // void showElevationGrid();
    // void showAzimuthGrid();
    // void show3dPlot();
    // void show2dPlot();
    // void calculateDataArray3d();
};
