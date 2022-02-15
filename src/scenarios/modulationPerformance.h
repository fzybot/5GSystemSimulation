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
#include <QPair>

#define NUMBER_OF_REP 1000


static void modulationToDoppler()
{

    int centralFrequency = 2600;
    QVector<QVector<QPair<float, float>>> data, dataBer;
    QVector<QPair<float, float>> localData2, localData2Ber;
    QVector<QPair<float, float>> localData4, localData4Ber;
    QVector<QPair<float, float>> localData6, localData6Ber;
    QVector<QPair<float, float>> localData8, localData8Ber;

    
    qDebug() << "Modulation Performance testing:";
    Signal signal, signal2;
    for (int i = 0; i < 500; i = i + 10)
    {
        QPair<float, float> pair2, pair4, pair6, pair8, 
                            pair2Ber, pair4Ber, pair6Ber, pair8Ber;

        Signal  signal_2600_2(centralFrequency, 15, 100, 0, 0),
                signal_2600_4(centralFrequency, 15, 100, 0, 0),
                signal_2600_6(centralFrequency, 15, 100, 0, 0),
                signal_2600_8(centralFrequency, 15, 100, 0, 0);

        signal_2600_2.transmitAndReceive(2, i);
        signal_2600_4.transmitAndReceive(4, i);
        signal_2600_6.transmitAndReceive(6, i);
        signal_2600_8.transmitAndReceive(8, i);

        pair2.first = i;
        pair2.second = signal_2600_2.getAverageEvm();

        pair4.first = i;
        pair4.second = signal_2600_4.getAverageEvm();

        pair6.first = i;
        pair6.second = signal_2600_6.getAverageEvm();

        pair8.first = i;
        pair8.second = signal_2600_8.getAverageEvm();

        pair2Ber.first = i;
        pair2Ber.second = signal_2600_2.getBER()[0];

        pair4Ber.first = i;
        pair4Ber.second = signal_2600_4.getBER()[0];

        pair6Ber.first = i;
        pair6Ber.second = signal_2600_6.getBER()[0];

        pair8Ber.first = i;
        pair8Ber.second = signal_2600_8.getBER()[0];

        localData2.push_back(pair2);
        localData4.push_back(pair4);
        localData6.push_back(pair6);
        localData8.push_back(pair8);

        localData2Ber.push_back(pair2Ber);
        localData4Ber.push_back(pair4Ber);
        localData6Ber.push_back(pair6Ber);
        localData8Ber.push_back(pair8Ber);

        if ( i == 100){
            signal_2600_2.printSignalInfo();
            signal_2600_4.printSignalInfo();
            signal_2600_6.printSignalInfo();
            signal_2600_8.printSignalInfo();
        }
    }
    data.push_back(localData2);
    data.push_back(localData4);
    data.push_back(localData6);
    data.push_back(localData8);

    dataBer.push_back(localData2Ber);
    dataBer.push_back(localData4Ber);
    dataBer.push_back(localData6Ber);
    dataBer.push_back(localData8Ber);

    signal.visualize2D(data, "QString str");
    signal2.visualize2D(dataBer, "QString str");

    // signal.fillRandomData(1, 16);
    // signal.modulateData(MO, signal.getDataArray());
    // signal.layersIFFT(signal.getModulatedIQ());
    // signal.layersFFT(signal.getSignalInTime());


}
