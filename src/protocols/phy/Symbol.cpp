#include "Symbol.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QtMath>

#include <armadillo>
#include <bitset>
#include <iostream>
#include <algorithm>

#include "src/visualization/Chartable.h"

// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

Symbol::Symbol()
{
    // powerValues_.resize(1);
}

Symbol::Symbol(int carrierFreq, int SCS, int bandwidth)
{
    configSignalSettings(carrierFreq, SCS, bandwidth);
}

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void Symbol::configSignalSettings(int bandLow, int SCS, int bandwidth)
{
    startFrequency_ = bandLow;
    startFrequencyHz_ = bandLow * qPow(10, 6);
    bandwidth_ = bandwidth;
    scs_ = SCS;
    calculateFFTSize();
    calculateSamplingTime();
}

void Symbol::configDopplerSettings(int dSpeed, int angle)
{
    calculateDoppler(getStartFreqHz(), angle, dSpeed);
}

int Symbol::getStartFreqMhz()
{
    return startFrequency_;
}

int Symbol::getStartFreqHz()
{
    return startFrequencyHz_;
}

void Symbol::setPowerValues(const QVector< QVector<double> > powerValues)
{
    powerValues_ = powerValues;
}

void Symbol::setIQValues(const QVector<QVector<arma::cx_double>>  IQvalues)
{
    IQvalues_ = IQvalues;
}

QVector<QVector<double>> &Symbol::getPowerValues()
{
    return powerValues_;
}

QVector<QVector<arma::cx_double>> &Symbol::getIQValues()
{
    return IQvalues_;
}

QVector<QVector<arma::cx_double>>   &Symbol::getSignalInTime()
{
    return signalInTime_;
}

QVector<QVector<arma::cx_double>>   &Symbol::getSignalInFreq()
{
    return signalInFreq_;
}

int Symbol::getFFTSize()
{
    return FFTSize_;
}

double Symbol::getSamplingTime()
{
    return samplingTime_;
}

double Symbol::getAverageEvm()
{
    return averageEVM_;
}

QVector<QVector<bool>> &Symbol::getDataArray()
{
    return dataArray_;
}

QVector<QVector<bool>> &Symbol::getDataArrayDemodulated()
{
    return dataArrayDemodulated_;
}

QVector<QVector<arma::cx_double>> &Symbol::getModulatedIQ()
{
    return modulatedIQ_;
}

double Symbol::getDopplerFreq()
{
    return dopplerFreq_;
}

// ----- [ FUNCTIONALITY ] ---------------------------------------------------------------------------------------------

void Symbol::calculateFFTSize()
{
    float diff = bandwidth_ * 1000 / scs_;
    numberOfFreq_ = (int)diff * 12;

    for (int i = 1; i <= 50; i ++) {
        if(qPow(2, i) >= diff){
            FFTSize_ = qPow(2, i);
            break;
        }
    }
}

void Symbol::calculateSamplingTime()
{
    // In [nanoSec]
    samplingTime_ = 1000 / ( static_cast<double>(scs_) * static_cast<double>(FFTSize_ / 1000) );
}

void Symbol::normalize(QVector<QVector<arma::cx_double>> &IQ, int byValue)
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

void Symbol::calculateDoppler(int carrierFreq, double angle, double speed)
{
    double angleRad = (angle * arma::datum::pi) / 180;
    double speedUe = (speed * 1000) / 3600;
    dopplerFreq_ = (speedUe * qCos(0) *carrierFreq) / c_;
}

Symbol* Symbol::copy(void)
{
    Symbol *txSignal = new Symbol();
    txSignal->setPowerValues(getPowerValues());
    txSignal->setIQValues(getIQValues());

    return txSignal;
}

void Symbol::fromTbToSignal(QVector<TransportBlock> tbContainer)
{

}

void Symbol::fillRandomData(int mimoSize, int length)
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


void Symbol::modulateData(int modulationOrder, QVector<QVector<bool>> &dataArray)
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

QVector<arma::cx_double> Symbol::QPSK(QVector<bool> &dataArray)
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

QVector<arma::cx_double> Symbol::QAM16(QVector<bool> &dataArray)
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

QVector<arma::cx_double> Symbol::QAM64(QVector<bool> &dataArray)
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

QVector<arma::cx_double> Symbol::QAM256(QVector<bool> &dataArray)
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


void Symbol::demodulateIQ(int modulationOrder, QVector<QVector<arma::cx_double>> &IQValues)
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

QVector<bool> Symbol::demQPSK(QVector<arma::cx_double> &IQValues)
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
        double min = 100000.0;
        int localIndex = 0;
        for (int j = 0; j < originalIQ.length(); j++){
            diff = qFabs( qSqrt(   qPow(originalIQ[j].real() - IQValues[i].real(), 2) + 
                            qPow(originalIQ[j].imag() - IQValues[i].imag(), 2)
                        ));
            // diff =  qFabs( 
            //                 qSqrt(qPow(originalIQ[j].real(), 2) + qPow(originalIQ[j].imag(), 2)) - 
            //                 qSqrt(qPow(IQValues[i].real(), 2) + qPow(IQValues[i].imag(), 2)) 
            //             );
            qDebug() << "Diff  = --> " << diff;
            if (diff <= min)
            {
                min = diff;
                localIndex = j;
            }
        }
        qDebug() << "EVM  = --> " << min;
        averageEVM_ += min;
        demodulatedData.push_back(originalModulation[localIndex * MO]);
        demodulatedData.push_back(originalModulation[localIndex*MO + 1]);
        //qDebug() << "localIndex = --> " << localIndex << originalModulation[localIndex*2] << originalModulation[localIndex*2+1];
    }
    averageEVM_ = averageEVM_ / IQValues.length();

    return demodulatedData;
}

QVector<bool> Symbol::demQAM16(QVector<arma::cx_double> &IQValues)
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

QVector<bool> Symbol::demQAM64(QVector<arma::cx_double> &IQValues)
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

QVector<bool> Symbol::demQAM256(QVector<arma::cx_double> &IQValues)
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

void Symbol::layersIFFT(QVector<QVector<arma::cx_double>> &modulatedIQ)
{
    int N = modulatedIQ.length();
    for (int i = 0; i < N; i++)
    {
        signalInTime_.push_back(IFFT(modulatedIQ[i]));
    }
}

QVector<arma::cx_double> Symbol::IFFT(QVector<arma::cx_double> vector)
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

void Symbol::layersFFT(QVector<QVector<arma::cx_double>> &timeIO)
{
    int N = timeIO.length();
    for (int i = 0; i < N; i++){
        signalInFreq_.push_back(FFT(timeIO[i]));
    }
}

QVector<arma::cx_double> Symbol::FFT(QVector<arma::cx_double> vector)
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

// void Signal::layersArmaIFFT(QVector<QVector<arma::cx_double>> &modulatedIQ, int size_fft)
// {
//     int N = modulatedIQ.length();
//     for (int i = 0; i < N; i++)
//     {
//         signalInTime_.push_back(armaIFFT(modulatedIQ[i], size_fft));
//     }
// }

// QVector<arma::cx_double> Signal::armaIFFT(QVector<arma::cx_double> vector, int size_fft)
// {
//     return arma::ifft(vector, size_fft);
// }

// void Signal::layersArmaFFT(QVector<QVector<arma::cx_double>> &timeIO, int size_fft)
// {
//     int N = timeIO.length();
//     for (int i = 0; i < N; i++){
//         signalInFreq_.push_back(armaFFT(timeIO[i], size_fft));
//     }
// }

// QVector<arma::cx_double> Signal::armaFFT(QVector<arma::cx_double> vector, int size_fft)
// {
//     return arma::fft(vector);
// }

void Symbol::layersIFFTCarrier( QVector<QVector<arma::cx_double>> &modulatedIQ, 
                                int numerology, double speed)
{
    int N = modulatedIQ.length();
    for (int i = 0; i < N; i++){
        signalInTime_.push_back(IFFTCarrier(modulatedIQ[i], numerology, speed));
    }
}


void Symbol::layersFFTCarrier(QVector<QVector<arma::cx_double>> &timeIO, int numerology)
{
    int N = timeIO.length();
    for (int i = 0; i < N; i++){
        signalInFreq_.push_back(FFTCarrier(timeIO[i], numerology));
    }
}

QVector<arma::cx_double> Symbol::IFFTCarrier(QVector<arma::cx_double> vector, int numerology, double speed)
{
    int N = vector.length();
    QVector<arma::cx_double> afterIFFT;

    //calculateDoppler(getStartFreqHz() + numerology * j, 0, speed);
    double dopplerRad =  (dopplerFreq_ / getStartFreqHz());
    for (int i = 0; i < N; i++)
    {
        double localSummReal = 0.0;
        double localSummImag = 0.0;
        double arg = 0.0;
        for (int j = 0; j < N; j++)
        {
            arg = (2 * arma::datum::pi * i * (j -  dopplerRad)) / N;
            localSummReal += (vector[j].real() * cos(arg)) - (vector[j].imag() * sin(arg));
            localSummImag += (vector[j].real() * sin(arg)) + (cos(arg) * vector[j].imag());
        }
        arma::cx_double value(localSummReal / N, localSummImag / N);
        afterIFFT.push_back(value);
    }
    return afterIFFT;
}

QVector<arma::cx_double> Symbol::FFTCarrier(QVector<arma::cx_double> vector, int numerology)
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
            arg = (2 * arma::datum::pi * i * (j) ) / N ;
            localSummReal += (vector[j].real() * cos(arg)) - (vector[j].imag() * (-1) * sin(arg));
            localSummImag += (vector[j].real() * (-1) * sin(arg)) + (cos(arg) * vector[j].imag());
        }
        arma::cx_double value(localSummReal, localSummImag);
        afterFFT.push_back(value);
    }

    return afterFFT;
}

void Symbol::compareData()
{
    int mimoN = dataArray_.length();
    int N = dataArray_[0].length();
    double BER = 0.0;
    for (int i = 0; i < mimoN; i++)
    {
        BER = 0.0;
        int count = 0;
        for (int j = 0; j < N; j++)
        {
            if (dataArray_[i][j] != dataArrayDemodulated_[i][j]){
                count++;
            }
        }
        BER = count / static_cast<double>(N) *100;
        BER_[0] = BER;
        qDebug() << "BER -> " << BER;
    }
}

QVector<double> &Symbol::getBER()
{
    return BER_;
}

double Symbol::transmitAndReceive(int MO, int speed)
{
    fillRandomData(1, 1000);
    modulateData(MO, getDataArray());
    //normalize(getModulatedIQ(), 100);
    layersIFFTCarrier(getModulatedIQ(), scs_ * 1000, speed);
    layersFFTCarrier(getSignalInTime(), scs_ * 1000);
    // layersIFFTCarrier(getModulatedIQ(), 0, getStartFreqHz(), 30 * 1000, 1);
    // layersFFTCarrier(getSignalInTime(), 0, getStartFreqHz(), 30 * 1000);
    demodulateIQ(MO, getSignalInFreq());
    compareData();
}

// void Signal::IFFT(QVector<arma::cx_double> vector, int size, int freq, int numerology)
// {

// }

// void Signal::dopplerIFFT(QVector<arma::cx_double> vector, int size, int freq, int numerology)
// {

// }

void Symbol::printIQValues(QVector<QVector<arma::cx_double>> &IQ, QString str)
{
    for (int i = 0; i < IQ.length(); i++)
    {
        for (int j = 0; j < IQ[i].length(); j++)
        {
            qDebug() << "Signal::" << str << IQ[i][j].real() << IQ[i][j].imag();
        }
    }
}

void Symbol::printSignalInfo()
{
    qDebug() << "Signal::printSignalInfo()--> ";
    qDebug() << "Signal::printSignalInfo()--> Freq: " << startFrequency_;
    qDebug() << "Signal::printSignalInfo()--> BW: " << bandwidth_;
    qDebug() << "Signal::printSignalInfo()--> SCS: " << scs_;
    qDebug() << "Signal::printSignalInfo()--> Samp. Rate: " << sampleRate_;
    qDebug() << "Signal::printSignalInfo()--> FFT Size: " << FFTSize_;
    qDebug() << "Signal::printSignalInfo()--> Samp. Time: " << samplingTime_;
    qDebug() << "Signal::printSignalInfo()--> Doppler Freq: " << dopplerFreq_;
    for (int i = 0; i < BER_.length(); i++){
        qDebug() << "Signal::printSignalInfo()--> BER: " << BER_[i];
    }
    qDebug() << "Signal::printSignalInfo()--> Aver. EVM: " << averageEVM_;
}

void Symbol::printData(QVector<QVector<bool>> &data)
{
    for (int i = 0; i < data.length(); i++)
    {
        qDebug() << "Data Array for antenna port " << '[' << i << "]: ";
        qDebug() << data[i];
    }
    
}
