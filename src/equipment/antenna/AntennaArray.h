#pragma once

#include <QVector>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>


class Custom3dSurface;

class AntennaArray
{
enum class AntennaType
    {
        ANTENNA_TYPE_OMNIDIRECTIONAL,
        ANTENNA_TYPE_3GPP_3D,
        ANTENNA_TYPE_3GPP_CUSTOM,
    };

private:

    AntennaArray::AntennaType type_;
    // The number of antennas inside array.
    int nVerical_ = 0;
    int nHorizon_ = 0;

    float elevation_;
    float azimuth_;
    QVector<float> elevationGrid_;
    QVector<float> azimuthGrid_;
    QVector<QVector<float>> Fa_;
    QVector<QVector<float>> Fb_;

    Custom3dSurface* surface_;
    QtDataVisualization::QSurfaceDataProxy *proxy3d_;
    QtDataVisualization::QSurfaceDataArray *dataArray_;

public:
    AntennaArray();
    AntennaArray(int sizeX, int sizeY);

    void setSize(int sizeX, int sizeY);

    void setAntennaType(AntennaType type);
    AntennaType getAntennaType();

    float calculateElevation(float angle);   // range [-90:90]
    float calculateAzimuth(float angle);     // range [-180:180]
    float getElevation(float angle);
    float getAzimuth(float angle);

    void calculateElevationGrid();
    void calculateAzimuthGrid();
    QVector<float> &getElevationGrid();
    QVector<float> &getAzimuthGrid();

    float calculateAntGain(float elevation, float azimuth);
    float calculateVerticalCutGain(float elevation);
    float calculateHorizontalCutGain(float azimuth);

    void showElevationGrid();
    void showAzimuthGrid();
    void visualize3D();
    void calculateDataArray3d();
    void visualize2D(float elevation);
};
