#include "Signal.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QtMath>

#include <armadillo>
#include <bitset>
#include <iostream>
#include <algorithm>

#include "src/visualization/Chartable.h"

// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

Signal::Signal()
{
    // powerValues_.resize(1);
}

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void Signal::configSignalSettings(int bandLow, int SCS, int bandwidth)
{
    startFrequency_ = bandLow;
    bandwidth_ = bandwidth;
    scs_ = SCS;
    calculateFFTSize();
    calculateSamplingTime();
}

void Signal::setPowerValues(const QVector< QVector<double> > powerValues)
{
    powerValues_ = powerValues;
}

void Signal::setIQValues(const QVector<QVector<arma::cx_double>>  IQvalues)
{
    IQvalues_ = IQvalues;
}

QVector<QVector<double>> &Signal::getPowerValues()
{
    return powerValues_;
}

QVector<QVector<arma::cx_double>> &Signal::getIQValues()
{
    return IQvalues_;
}

QVector<QVector<arma::cx_double>>   &Signal::getSignalInTime()
{
    return signalInTime_;
}

QVector<QVector<arma::cx_double>>   &Signal::getSignalInFreq()
{
    return signalInFreq_;
}

int Signal::getFFTSize()
{
    return FFTSize_;
}

double Signal::getSamplingTime()
{
    return samplingTime_;
}

float Signal::getAverageEvm()
{
    return averageEVM_;
}

QVector<QVector<bool>> &Signal::getDataArray()
{
    return dataArray_;
}

QVector<QVector<bool>> &Signal::getDataArrayDemodulated()
{
    return dataArrayDemodulated_;
}

QVector<QVector<arma::cx_double>> &Signal::getModulatedIQ()
{
    return modulatedIQ_;
}

// ----- [ FUNCTIONALITY ] ---------------------------------------------------------------------------------------------

void Signal::calculateFFTSize()
{
    float diff = bandwidth_ * 1000 / scs_;

    for (int i = 1; i <= 50; i ++) {
        if(qPow(2, i) >= diff){
            FFTSize_ = qPow(2, i);
            break;
        }
    }
}

void Signal::calculateSamplingTime()
{
    // In [nanoSec]
    samplingTime_ = 1000 / ( static_cast<double>(scs_) * static_cast<double>(FFTSize_ / 1000) );
}

void Signal::normalize(QVector<QVector<arma::cx_double>> &IQ, int byValue)
{
    double max = -1000000;
    for (int i = 0; i < IQ.length(); i++)
    {
        for (int j = 0; j < IQ[i].length(); j++)
        {
            if(qFabs(IQ[i][j].real()) >= max){
                max = qFabs(IQ[i][j].real());
            }
            if(qFabs(IQ[i][j].imag()) >= max){
                max = qFabs(IQ[i][j].imag());
            }
        }
    }
    double real;
    double imag;
    for (int i = 0; i < IQ.length(); i++)
    {
        for (int j = 0; j < IQ[i].length(); j++)
        {
            real = (IQ[i][j].real() / max) * byValue;
            imag = (IQ[i][j].imag() / max) * byValue;
            arma::cx_double value(real, imag);
            IQ[i][j] = value;
        }
    }
}

Signal* Signal::copy(void)
{
    Signal *txSignal = new Signal();
    txSignal->setPowerValues(getPowerValues());
    txSignal->setIQValues(getIQValues());

    return txSignal;
}

void Signal::fromTbToSignal(QVector<TransportBlock> tbContainer)
{

}

void Signal::fillRandomData(int mimoSize, int length)
{
    QVector<bool> oneLayer;
    for (int i = 0; i < mimoSize; i++)
    {
        oneLayer.clear();
        for (int j = 0; j < length; j++) {
            int x = QRandomGenerator::global()->bounded(0, 100);
            if(x < 50){
                oneLayer.push_back(false);
            } else {
                oneLayer.push_back(true);
            }
        }
        getDataArray().append(oneLayer);
    }
}


void Signal::modulateData(int modulationOrder, QVector<QVector<bool>> &dataArray)
{
    int N = dataArray.length();
    switch (modulationOrder)
    {
    case 2:
        for (int i = 0; i < N; i++){
            modulatedIQ_.push_back(QPSK(dataArray[i]));
        }
        //qDebug() << "modulateData --> " << modulatedIO_[0](0).real() << modulatedIO_[0](0).imag();
        break;
    case 4:
        for (int i = 0; i < N; i++){
            modulatedIQ_.push_back(QAM16(dataArray[i]));
        }
        break;
    case 6:
        for (int i = 0; i < N; i++){
            modulatedIQ_.push_back(QAM64(dataArray[i]));
        }
        break;
    case 8:
        for (int i = 0; i < N; i++){
            modulatedIQ_.push_back(QAM256(dataArray[i]));
        }
        break;
    }
}

QVector<arma::cx_double> Signal::QPSK(QVector<bool> &dataArray)
{
    QVector<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 2){
        double real = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray[i]);
        double imag = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray[i + 1]);
        arma::cx_double value(real, imag);
        //qDebug() << "QPSK --> " << value.real() << value.imag();
        modulated.push_back(value);
    }
    return modulated;
}

QVector<arma::cx_double> Signal::QAM16(QVector<bool> &dataArray)
{
    QVector<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 4){
        double real = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray[i]) * (2 - (1 - dataArray[i+2]));
        double imag = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray[i + 1]) * (2 - (1 - dataArray[i+3])); 
        arma::cx_double value(real, imag);
        //qDebug() << "QAM16 --> " << value.real() << value.imag();
        modulated.push_back(value);
    }
    return modulated;
}

QVector<arma::cx_double> Signal::QAM64(QVector<bool> &dataArray)
{
    QVector<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 6){
        double real = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray[i]) * 
                                            (4 - (1 - 2 * dataArray[i+2])) * (2 - (1 - dataArray[i+4]));
        double imag = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray[i + 1]) * 
                                            (4 - (1 - 2 * dataArray[i+3])) * (2 - (1 - dataArray[i+5])); 
        arma::cx_double value(real, imag);
        //qDebug() << "QAM64 --> " << value.real() << value.imag();
        modulated.push_back(value);
    }
    return modulated;
}

QVector<arma::cx_double> Signal::QAM256(QVector<bool> &dataArray)
{
    QVector<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 8){
        double real = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray[i]) * (8 - (1 - 2 * dataArray[i+2])) * 
                        (4 - (1 - 2 * dataArray[i+4])) * (2 - (1 - dataArray[i+6]));
        double imag = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray[i + 1]) * (8 - (1 - 2 * dataArray[i+3])) * 
                        (4 - (1 - 2 * dataArray[i+5])) * (2 - (1 - dataArray[i+7])); 
        arma::cx_double value(real, imag);
        //qDebug() << "QAM256 --> " << value.real() << value.imag();
        modulated.push_back(value);
    }
    return modulated;
}


void Signal::demodulateIQ(int modulationOrder, QVector<QVector<arma::cx_double>> &IQValues)
{
    int N = IQValues.length();

    switch (modulationOrder)
    {
    case 2:
        for (int i = 0; i < N; i++){
            dataArrayDemodulated_.append(demQPSK(IQValues[i]));
        }
        break;
    case 4:
        for (int i = 0; i < N; i++){
            dataArrayDemodulated_.append(demQAM16(IQValues[i]));
        }
        break;
    case 6:
        for (int i = 0; i < N; i++){
            dataArrayDemodulated_.append(demQAM64(IQValues[i]));
        }
        break;
    case 8:
        for (int i = 0; i < N; i++){
            dataArrayDemodulated_.append(demQAM256(IQValues[i]));
        }
        break;
    }
}

QVector<bool> Signal::demQPSK(QVector<arma::cx_double> &IQValues)
{
    int MO = 2;
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;

    for (int i = 0; i < qPow(2, MO); i++){
        std::bitset<2>      bitArray(i);
        originalModulation.push_back(bitArray[1]);
        originalModulation.push_back(bitArray[0]);
    }
    QVector<arma::cx_double> originalIQ;
    originalIQ = QPSK(originalModulation);
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
        demodulatedData.push_back(originalModulation[localIndex * MO]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 1]);
        //qDebug() << "localIndex = --> " << localIndex << originalModulation[localIndex*2] << originalModulation[localIndex*2+1];
    }
    averageEVM_ = averageEVM_ / IQValues.length();

    return demodulatedData;
}

QVector<bool> Signal::demQAM16(QVector<arma::cx_double> &IQValues)
{
    int MO = 4;
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;
    for (int i = 0; i < qPow(2, MO); i++){
        std::bitset<4>      bitArray(i);
        originalModulation.push_back(bitArray[3]);
        originalModulation.push_back(bitArray[2]);
        originalModulation.push_back(bitArray[1]);
        originalModulation.push_back(bitArray[0]);
    }
    QVector<arma::cx_double> originalIQ;
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

QVector<bool> Signal::demQAM64(QVector<arma::cx_double> &IQValues)
{
    int MO = 6;  
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;
    for (int i = 0; i < qPow(2, MO); i++){
        std::bitset<6>      bitArray(i);
        originalModulation.push_back(bitArray[5]);
        originalModulation.push_back(bitArray[4]);
        originalModulation.push_back(bitArray[3]);
        originalModulation.push_back(bitArray[2]);
        originalModulation.push_back(bitArray[1]);
        originalModulation.push_back(bitArray[0]);
    }
    QVector<arma::cx_double> originalIQ;
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

QVector<bool> Signal::demQAM256(QVector<arma::cx_double> &IQValues)
{
    int MO = 8;  
    QVector<bool> demodulatedData;
    QVector<bool> originalModulation;
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
    QVector<arma::cx_double> originalIQ;
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
    // for (int i = 0; i < demodulatedData.length();i++){
    //     qDebug() << "Demodulated Data = --> " << demodulatedData[i];
    // }
    averageEVM_ = averageEVM_ / IQValues.length();
    return demodulatedData;
}

// void Signal::makeIFFT(QVector<arma::cx_double> vector, int size)
// {
//     arma::vec X(100, arma::fill::randu);
//     arma::cx_vec Y = arma::fft(X, 128);
//     for(int i = 0; i < Y.size(); i++){
//         qDebug() <<" FFT -->" << Y(i).real();
//     }
// }

void Signal::layersIFFT(QVector<QVector<arma::cx_double>> &modulatedIQ)
{
    int N = modulatedIQ.length();
    for (int i = 0; i < N; i++)
    {
        signalInTime_.push_back(IFFT(modulatedIQ[i]));
    }
}

QVector<arma::cx_double> Signal::IFFT(QVector<arma::cx_double> vector)
{
    int N = vector.length();
    QVector<arma::cx_double> afterIFFT;
    for (int i = 0; i < N; i++)
    {
        double localSummReal = 0.0;
        double localSummImag = 0.0;
        double arg = 0.0;
        for (int j = 0; j < N; j++)
        {
            arg = (2 * arma::datum::pi * j * i) / N;
            localSummReal += (vector[j].real() * cos(arg)) - (vector[j].imag() * sin(arg));
            localSummImag += (vector[j].real() * sin(arg)) + (cos(arg) * vector[j].imag());
        }
        arma::cx_double value(localSummReal / N, localSummImag / N);
        afterIFFT.push_back(value);
    }

    return afterIFFT;
}

void Signal::layersFFT(QVector<QVector<arma::cx_double>> &timeIO)
{
    int N = timeIO.length();
    for (int i = 0; i < N; i++){
        signalInFreq_.push_back(FFT(timeIO[i]));
    }
}

QVector<arma::cx_double> Signal::FFT(QVector<arma::cx_double> vector)
{
    int N = vector.length();
    QVector<arma::cx_double> afterFFT;
    for (int i = 0; i < N; i++)
    {
        double localSummReal = 0.0;
        double localSummImag = 0.0;
        double arg = 0;
        for (int j = 0; j < N; j++)
        {
            arg = (2 * arma::datum::pi * j * i) / N ;
            localSummReal += (vector[j].real() * cos(arg)) - (vector[j].imag() * (-1) * sin(arg));
            localSummImag += (vector[j].real() * (-1) * sin(arg)) + (cos(arg) * vector[j].imag());
            //qDebug() << "IFFT " << arg << vector[j].real() << vector[j].imag();
            //qDebug() << "FFT --->  " << i << j << arg << vector[j].real() << vector[j].imag() << localSummReal << localSummImag;
        }
        //qDebug() << "IFFT " << localSummReal << localSummImag;
        arma::cx_double value(localSummReal, localSummImag);
        afterFFT.push_back(value);
    }

    return afterFFT;   
}

void Signal::layersIFFTCarrier(QVector<QVector<arma::cx_double>> &modulatedIQ, int size, int freq, int numerology, double doppler)
{


}

void Signal::layersFFTCarrier(QVector<QVector<arma::cx_double>> &timeIO, int size, int freq, int numerology)
{


}

QVector<arma::cx_double> Signal::IFFTCarrier(QVector<arma::cx_double> vector, int size, int freq, int numerology, double doppler)
{

    return 0;
}

QVector<arma::cx_double> Signal::FFTCarrier(QVector<arma::cx_double> vector, int size, int freq, int numerology)
{

    return 0;
}

// void Signal::IFFT(QVector<arma::cx_double> vector, int size, int freq, int numerology)
// {

// }

// void Signal::dopplerIFFT(QVector<arma::cx_double> vector, int size, int freq, int numerology)
// {

// }

void Signal::printIQValues(QVector<QVector<arma::cx_double>> &IQ, QString str)
{
    for (int i = 0; i < IQ.length(); i++)
    {
        for (int j = 0; j < IQ[i].length(); j++)
        {
            qDebug() << "Signal::" << str << IQ[i][j].real() << IQ[i][j].imag();
        }
    }
}
