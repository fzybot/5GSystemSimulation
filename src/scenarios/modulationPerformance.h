#pragma once

#include "src/equipment/Equipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Walker.h"
#include "src/protocols/phy/Channel/propagationModels.h"
#include "src/simulation/Simulation.h"
#include "src/protocols/phy/Bandwidth.h"
#include "src/protocols/phy/Symbol.h"
#include "src/equipment/antenna/AntennaArray.h"
#include "src/visualization/Chartable.h"
#include "src/protocols/phy/modulation.h"
#include "src/protocols/phy/fft.h"

//#include <armadillo>

#include <QDebug>
#include <QPair>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>


#define NUMBER_OF_REP 1000

QVector<bool> generateRandomData(int length)
{
    QVector<bool> oneLayer;

    for (int j = 0; j < length; j++) {
        int x = QRandomGenerator::global()->bounded(0, 100);
        if(x <= 50){
            oneLayer.push_back(false);
        } else {
            oneLayer.push_back(true);
        }
    }
    return oneLayer;
}

void printIQValues(QVector<std::complex<double>> &IQ, QString str)
{

    for (int j = 0; j < IQ.length(); j++)
    {
        qDebug() << str << IQ[j].real() << IQ[j].imag();
    }
}

double compareData(QVector<bool> data_1, QVector<bool> data_2)
{
    int N = data_1.length();
    double BER = 0.0;
    int count = 0;
    for (int j = 0; j < N; j++)
    {
        if (data_1[j] != data_2[j]){
            count++;
        }
    }
    BER = count / static_cast<double>(N) *100;
    return BER;
}

void modulationPerformance(){

    QVector<bool> data = {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1};
    qDebug() <<"random data" << data << data.length();

    QVector<std::complex<double>> modulated_qpsk;
    QVector<std::complex<double>> modulated_qam16;
    QVector<std::complex<double>> modulated_qam64;
    QVector<std::complex<double>> modulated_qam256;

    QVector<bool> demodulated_qpsk;
    QVector<bool> demodulated_qam16;
    QVector<bool> demodulated_qam64;
    QVector<bool> demodulated_qam256;


    QVector<std::complex<double>> ifft_qpsk;
    QVector<std::complex<double>> ifft_qam16;
    QVector<std::complex<double>> ifft_qam64;
    QVector<std::complex<double>> ifft_qam256;

    QVector<std::complex<double>> fft_qpsk;
    QVector<std::complex<double>> fft_qam16;
    QVector<std::complex<double>> fft_qam64;
    QVector<std::complex<double>> fft_qam256;



    modulated_qpsk = QPSK(data);
    ifft_qpsk = ifft(modulated_qpsk);
    // add channel
    fft_qpsk = fft(ifft_qpsk);
    demodulated_qpsk = demQPSK(fft_qpsk);
    printIQValues(modulated_qpsk, "qpsk modulated: ");
    qDebug() << "qpsk demodulated data: " << demodulated_qpsk;
    qDebug() << "BER qpsk: " << compareData(data, demodulated_qpsk);
}
