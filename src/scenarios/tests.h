#pragma once


#include "src/equipment/Equipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Walker.h"
#include "src/protocols/phy/propagationModels.h"
#include "src/simulation/Simulation.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/phy/Symbol.h"
#include "src/equipment/antenna/AntennaArray.h"

#include <armadillo>
//#include <fftw3.h>

#include <QDebug>


static void simpleTest()
{
//    gNodeB bs1;
//    qDebug() << bs1.PCI << bs1.bandwidth << "Number of BS: " << bs1.dataSize;
//    Simulation sim1;
//    qDebug() <<"Path Loss:" << sim1.calculatePathLoss(100, 0);
//    qDebug() <<"SINR:" << sim1.userEqipmnets[0].SINR;
    /*
    for (int i = 0; i < sim1.userEqipmnets.length(); ++i){
        qDebug() <<"SINR:" << sim1.userEqipmnets[i].SINR;
        qDebug() << "Step size:" << sim1.userEqipmnets[i].speed;
        qDebug() << "Step size:" << sim1.userEqipmnets[i].stepSize;
        qDebug() << "Longtitude: " << sim1.userEqipmnets[i].longtitude;
        qDebug() << "Latitude: "<< sim1.userEqipmnets[i].latitude;
        qDebug() <<"---------------------------------";
   }
   */
//    sim1.showBordersll();


    //**************************************************************
    // Bandwidth class test
    //**************************************************************
    // Bandwidth band("FR1", "n1", 15, 10, 20, 0, 0, false);
    // band.print();
    // qDebug() << PRBs_for_BW["FR2"][60][100];


    //**************************************************************
    // Signal class tests
    //**************************************************************

    // Signal signal;
    // signal.configSignalSettings(2100, 15, 100);
    // qDebug() << "FFT Size = " << signal.getFFTSize();
    // qDebug() << "Sampling Time = " << signal.getSamplingTime();
    // arma::cx_double value(0., 1.);
    // arma::Col<arma::cx_double> vector;
    // vector << value;
    // qDebug() << "arma::cx_dmat = " << value.imag();
    // qDebug() << "arma::cx_dmat = " << value.real();
    // qDebug() << "arma::Col<arma::cx_double> = " << vector(0).imag();
    // QVector<bool> test;
    // test << 0 << 1 << 1;
    // qDebug() << "QVector<bool> test = " << test[0] << test[1] << test[2];

    //**************************************************************
    // Modulation test
    //**************************************************************

    int centralFrequency = 2600;
    int scs = 15;
    int bw = 100;
    int speed = 100;
    int MO = 2;

    Symbol signal(centralFrequency, scs, bw);

    signal.fillRandomData(1, 16);
    signal.modulateData(MO, signal.getDataArray());
    signal.printIQValues(signal.getModulatedIQ());
    qDebug() << "EVM --> " << signal.getAverageEvm();
    //signal.normalize(signal.getModulatedIQ(), 1);
    signal.layersIFFTCarrier(signal.getModulatedIQ(), scs, speed);
    // signal.printIQValues(signal.getSignalInTime(), "IFFT--> ");
    signal.layersFFTCarrier(signal.getSignalInTime(), scs);
    signal.printIQValues(signal.getSignalInFreq(), "FFT--> ");
    signal.demodulateIQ(MO, signal.getSignalInFreq());
    // signal.printData(signal.getDataArray());
    // signal.printData(signal.getDataArrayDemodulated());
    signal.compareData();
    signal.printSignalInfo();

    // AntennaArray ant1;
    // ant1.calculateElevationGrid();
    // ant1.calculateAzimuthGrid();
    //ant1.show3dPlot();
    //ant1.show2dPlot();


    //**************************************************************
    // Armadillo test
    //**************************************************************

    arma::cx_vec y;
    y << 1 << 2;
    
    qDebug() << "Arma test --> " << y.size();

    // for (int elev = 0; elev <= 180; elev++){
    //     for (int azim = -180; azim <= 180; azim++){
    //         qDebug() << "Ant Gain --> " << ant1.calculateAntGain(elev, azim);
    //     }
    // }
}
