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

private:
    float _azimuthAngle;
    float _elevationAngle;

    AntennaArrayNR::AntennaType _type;
    QVector<QVector<Beam *>> _beamContainer;
public:
    AntennaArrayNR();
    AntennaArrayNR(float azimuthAnge, float elevationAnge, AntennaArrayNR::AntennaType type, int nYAxis, int nXAxis, int sectorWidth);

    QVector<QVector<Beam *>> getBeams() const;
};

