#include "gNodeB.h"


gNodeB::gNodeB()
{
    PCI = 123;
    TxPower = 43;
    antennaGain = 18;
    otherLosses = 0;
    noiseFigure = 3;
    reqSINR = -3.3;
    bandwidth = 10;
    calculateThermalNoise();
    RxSensitivity = thermalNoise + noiseFigure + reqSINR;
    calculateEIRP();

    height = 60;

    dataSize = ((bandwidth * 1000) / SCS) * 2 * 14 * mimoLayers;
}