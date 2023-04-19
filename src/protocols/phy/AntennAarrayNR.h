#pragma once

#include <QVector>

class Beam;

class AntennaArrayNR
{
public:
enum class AntennaType
    {
        ANTENNA_TYPE_OMNIDIRECTIONAL,
        ANTENNA_TYPE_3GPP_3D,
        ANTENNA_TYPE_3GPP_CUSTOM,
    };

public:
    float _azimuthAngle;
    float _elevationAngle;

    AntennaArrayNR::AntennaType _type;
    QVector<QVector<Beam *>> _beamContainer;
public:
    AntennaArrayNR();
    AntennaArrayNR(AntennaArrayNR::AntennaType type, int nX, int nY, int sectorWidth);
};

