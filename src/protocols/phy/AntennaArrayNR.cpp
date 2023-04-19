#include <QDebug>

#include "AntennAarrayNR.h"
#include "src/equipment/antenna/Beam.h"

AntennaArrayNR::AntennaArrayNR()
{

}


void AntennaArrayNR::config(float azimuthAngle, float elevationAngle, AntennaArrayNR::AntennaType type, int nYAxis, int nXAxis, int sectorWidth)
{
    _azimuthAngle = azimuthAngle;
    _elevationAngle = elevationAngle;
    _type = type;
    float beamWidth = sectorWidth / nXAxis;
    float deltaAngle = _azimuthAngle - (sectorWidth / 2);
    _beamContainer.resize(nYAxis);
    for(int i = 0; i < nYAxis; i++){
        _beamContainer[i].resize(nXAxis);
        for(int j = 0; j < nXAxis; j++){
            Beam beam;
            beam.config();
            _beamContainer[i][j] = beam;
        }

    }
    
}

QVector<QVector<Beam>> AntennaArrayNR::getBeams() const
{
    return _beamContainer;
}
