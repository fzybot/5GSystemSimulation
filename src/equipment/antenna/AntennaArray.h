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

    AntennaType type_;
    // The number of antennas inside array.
    int nVerical_ = 0;
    int nHorizon_ = 0;

    float elevation_;
    float azimuth_;
    QVector<float> elevationGrid_;
    QVector<float> azimuthGrid_;
    QVector<QVector<float>> Fa_;
    QVector<QVector<float>> Fa_;

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

    void showElevationGrid();
    void showAzimuthGrid();
};

