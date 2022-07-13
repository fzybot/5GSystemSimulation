
#include "modulation.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QtMath>
#include <bitset>
#include <iostream>
#include <algorithm>

QVector<std::complex<double>> QPSK(QVector<bool> &dataArray)
{
    QVector<std::complex<double>> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 2){
        double real = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray[i]);
        double imag = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray[i + 1]);
        std::complex<double> value(real, imag);
        modulated.push_back(value);
    }
    return modulated;
}

QVector<std::complex<double>> QAM16(QVector<bool> &dataArray)
{
    QVector<std::complex<double>> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 4){
        double real = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray[i]) * (2 - (1 - dataArray[i+2]));
        double imag = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray[i + 1]) * (2 - (1 - dataArray[i+3])); 
        std::complex<double> value(real, imag);
        modulated.push_back(value);
    }
    return modulated;
}

QVector<std::complex<double>> QAM64(QVector<bool> &dataArray)
{
    QVector<std::complex<double>> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 6){
        double real = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray[i]) * 
                                            (4 - (1 - 2 * dataArray[i+2])) * (2 - (1 - dataArray[i+4]));
        double imag = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray[i + 1]) * 
                                            (4 - (1 - 2 * dataArray[i+3])) * (2 - (1 - dataArray[i+5])); 
       std::complex<double> value(real, imag);
        modulated.push_back(value);
    }
    return modulated;
}

QVector<std::complex<double>> QAM256(QVector<bool> &dataArray)
{
    QVector<std::complex<double>> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 8){
        double real = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray[i]) * (8 - (1 - 2 * dataArray[i+2])) * 
                        (4 - (1 - 2 * dataArray[i+4])) * (2 - (1 - dataArray[i+6]));
        double imag = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray[i + 1]) * (8 - (1 - 2 * dataArray[i+3])) * 
                        (4 - (1 - 2 * dataArray[i+5])) * (2 - (1 - dataArray[i+7])); 
        std::complex<double> value(real, imag);
        modulated.push_back(value);
    }
    return modulated;
}


QVector<bool> demQPSK(QVector<std::complex<double>> &IQValues)
{
    int MO = 2;
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;
    double averageEVM_ = 0;

    for (int i = 0; i < qPow(2, MO); i++){
        std::bitset<2>      bitArray(i);
        originalModulation.push_back(bitArray[1]);
        originalModulation.push_back(bitArray[0]);
    }
    QVector<std::complex<double>> originalIQ;
    originalIQ = QPSK(originalModulation);
    for (int i = 0; i < IQValues.length(); i++){
        double diff = 0;
        double min = 100000.0;
        int localIndex = 0;
        for (int j = 0; j < originalIQ.length(); j++){
            diff = qFabs( qSqrt(   qPow(originalIQ[j].real() - IQValues[i].real(), 2) + 
                            qPow(originalIQ[j].imag() - IQValues[i].imag(), 2)
                        ));
            if (diff <= min)
            {
                min = diff;
                localIndex = j;
            }
        }
        averageEVM_ += min;
        demodulatedData.push_back(originalModulation[localIndex * MO]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 1]);
    }
    averageEVM_ = averageEVM_ / IQValues.length();
    qDebug() << "EVM: " << averageEVM_;
    return demodulatedData;
}

QVector<bool> demQAM16(QVector<std::complex<double>> &IQValues)
{
    int MO = 4;
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;
    double averageEVM_ = 0;

    for (int i = 0; i < qPow(2, MO); i++){
        std::bitset<4>      bitArray(i);
        originalModulation.push_back(bitArray[3]);
        originalModulation.push_back(bitArray[2]);
        originalModulation.push_back(bitArray[1]);
        originalModulation.push_back(bitArray[0]);
    }
    QVector<std::complex<double>> originalIQ;
    originalIQ = QAM16(originalModulation);
    for (int i = 0; i < IQValues.length(); i++){
        double diff = 0;
        double min = 100000.;
        int localIndex = 0;
        for (int j = 0; j < originalIQ.length(); j++){
            diff = qSqrt(   qPow(originalIQ[j].real() - IQValues[i].real(), 2) + 
                            qPow(originalIQ[j].imag() - IQValues[i].imag(), 2)
                        );
            if(diff <= min){
                min = diff;
                localIndex = j;
            }
        }
        averageEVM_ += min;
        demodulatedData.push_back(originalModulation[localIndex*MO]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 1]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 2]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 3]);
    }
    averageEVM_ = averageEVM_ / IQValues.length();
    return demodulatedData;
}

QVector<bool> demQAM64(QVector<std::complex<double>> &IQValues)
{
    int MO = 6;  
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;
    double averageEVM_ = 0;

    for (int i = 0; i < qPow(2, MO); i++)
    {
        std::bitset<6>      bitArray(i);
        originalModulation.push_back(bitArray[5]);
        originalModulation.push_back(bitArray[4]);
        originalModulation.push_back(bitArray[3]);
        originalModulation.push_back(bitArray[2]);
        originalModulation.push_back(bitArray[1]);
        originalModulation.push_back(bitArray[0]);
    }
    QVector<std::complex<double>> originalIQ;
    originalIQ = QAM64(originalModulation);
    for (int i = 0; i < IQValues.length(); i++){
        double diff = 0;
        double min = 100000.;
        int localIndex = 0;
        for (int j = 0; j < originalIQ.length(); j++){
            diff = qSqrt(   qPow(originalIQ[j].real() - IQValues[i].real(), 2) + 
                            qPow(originalIQ[j].imag() - IQValues[i].imag(), 2)
                        );
            if(diff <= min){
                min = diff;
                localIndex = j;
            }
        }
        averageEVM_ += min;
        demodulatedData.push_back(originalModulation[localIndex*MO]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 1]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 2]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 3]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 4]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 5]);
    }
    averageEVM_ = averageEVM_ / IQValues.length();
    return demodulatedData;
}

QVector<bool> demQAM256(QVector<std::complex<double>> &IQValues)
{
    int MO = 8;  
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;
    double averageEVM_ = 0;

    for (int i = 0; i < qPow(2, MO); i++){
        std::bitset<8>      bitArray(i);
        originalModulation.push_back(bitArray[7]);
        originalModulation.push_back(bitArray[6]);
        originalModulation.push_back(bitArray[5]);
        originalModulation.push_back(bitArray[4]);
        originalModulation.push_back(bitArray[3]);
        originalModulation.push_back(bitArray[2]);
        originalModulation.push_back(bitArray[1]);
        originalModulation.push_back(bitArray[0]);
    }
    QVector<std::complex<double>> originalIQ;
    originalIQ = QAM256(originalModulation);
    for (int i = 0; i < IQValues.length(); i++){
        double diff = 0;
        double min = 100000.;
        int localIndex = 0;
        for (int j = 0; j < originalIQ.length(); j++){
            diff = qSqrt(   qPow(originalIQ[j].real() - IQValues[i].real(), 2) + 
                            qPow(originalIQ[j].imag() - IQValues[i].imag(), 2)
                        );
            if(diff <= min){
                min = diff;
                localIndex = j;
            }
        }
        averageEVM_ += min;
        demodulatedData.push_back(originalModulation[localIndex*MO]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 1]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 2]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 3]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 4]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 5]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 6]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 7]);
    }
    averageEVM_ = averageEVM_ / IQValues.length();
    return demodulatedData;
}


