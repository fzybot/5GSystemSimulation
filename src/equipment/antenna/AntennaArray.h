#pragma once

#include <QVector>


class AntennaArray
{
enum class AntennaType
    {
        ANTENNA_TYPE_OMNIDIRECTIONAL,
        ANTENNA_TYPE_TRI_SECTOR,
        ANTENNA_TYPE_FOUR_SECTOR,
        ANTENNA_TYPE_SIX_SECTOR
    };

private:
    // The number of antennas inside array.
    int nVerical_ = 0;
    int nHorizon_ = 0;

    float elevation_;
    float azimuth_;
    QVector<float> elevationGrid_;
    QVector<float> azimuthGrid_;

public:
    AntennaArray();
    AntennaArray(int sizeX, int sizeY);

    void setSize(int sizeX, int sizeY);

    float calculateElevation(float angle);   // range [-90:90]
    float calculateAzimuth(float angle);     // range [-180:180]
    float getElevation(float angle);
    float getAzimuth(float angle);

    void calculateElevationGrid();
    void calculateAzimuthGrid();
    QVector<float> &getElevationGrid();
    QVector<float> &getAzimuthGrid();

    void showElevationGrid();
    void showAzimuthGrid();
};

