#pragma once

#include "src/equipment/Equipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Walker.h"
#include "src/protocols/phy/propagationModels.h"
#include "src/simulation/Simulation.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/phy/Signal.h"
#include "src/equipment/antenna/AntennaArray.h"

#include <armadillo>

#include <QDebug>


static void modulationToDoppler(int MO)
{

    int centralFrequency = 2600;
    Signal signal;
    signal.fillRandomData(1, 16);
    signal.modulateData(MO, signal.getDataArray());
    signal.layersIFFT(signal.getModulatedIQ());
    signal.layersFFT(signal.getSignalInTime());
    // signal.printIQValues(signal.getModulatedIQ());
    // qDebug() << "EVM --> " << signal.getAverageEvm();
    // //signal.normalize(signal.getModulatedIQ(), 1);
    // 
    // signal.printIQValues(signal.getSignalInTime(), "IFFT--> ");
    // 
    // signal.printIQValues(signal.getSignalInFreq(), "FFT--> ");
    // signal.demodulateIQ(2, signal.getSignalInFreq());

}
