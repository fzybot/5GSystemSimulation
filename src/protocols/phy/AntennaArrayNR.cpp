#include "AntennAarrayNR.h"

AntennaArrayNR::AntennaArrayNR()
{

}


AntennaArrayNR::AntennaArrayNR(float azimuthAngle, float elevationAngle, AntennaArrayNR::AntennaType type, int nYAxis, int nXAxis, int sectorWidth)
{
    _azimuthAngle = azimuthAngle;
    _elevationAngle = elevationAngle;
    _type = type;
    _beamContainer.resize(nYAxis);
    for(int i = 0; i < nYAxis; i++){
        _beamContainer[i].resize(nXAxis);
    }
    
}

QVector<QVector<Beam *>> AntennaArrayNR::getBeams() const
{
    return _beamContainer;
}
