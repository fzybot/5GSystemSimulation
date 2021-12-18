#include "Signal.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QtMath>

#include <armadillo>

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

void Signal::setIOValues(const QVector<arma::Col<arma::cx_double>>  IOvalues)
{
    IOvalues_ = IOvalues;
}

QVector<QVector<double>> &Signal::getPowerValues()
{
    return powerValues_;
}

QVector<arma::Col<arma::cx_double>> &Signal::getIOValues()
{
    return IOvalues_;
}

int Signal::getFFTSize()
{
    return FFTSize_;
}

double Signal::getSamplingTime()
{
    return samplingTime_;
}

QVector<bool> &Signal::getDataArray()
{
    return dataArray_;
}

QVector<QVector<bool>> &Signal::getDataArrayDemodulated()
{
    return dataArrayDemodulated_;
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

Signal* Signal::copy(void)
{
    Signal *txSignal = new Signal();
    txSignal->setPowerValues(getPowerValues());
    txSignal->setIOValues(getIOValues());

    return txSignal;
}

void Signal::fromTbToSignal(QVector<TransportBlock> tbContainer)
{

}

void Signal::fillRandomData(int mimoSize, int length)
{
    dataArray_ << 0 << 1 << 1 << 0 << 0 << 1 << 0 << 1 << 1 << 1 << 0 << 1 << 0 << 0 << 0 << 0;
}


void Signal::modulateData(int modulationOrder, QVector<bool> &dataArray)
{
    switch (modulationOrder)
    {
    case 2:
        modulatedIO_.append(QPSK(dataArray));
        //qDebug() << "modulateData --> " << modulatedIO_[0](0).real() << modulatedIO_[0](0).imag();
        break;
    case 4:
        modulatedIO_.append(QAM16(dataArray));
        break;
    case 6:
        modulatedIO_.append(QAM64(dataArray));
        break;
    case 8:
        modulatedIO_.append(QAM256(dataArray));
        break;
    }
}

arma::Col<arma::cx_double> Signal::QPSK(QVector<bool> &dataArray)
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 2){
        double real = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray[i]);
        double imag = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray[i + 1]);
        arma::cx_double value(real, imag);
        qDebug() << "QPSK --> " << value.real() << value.imag();
        modulated << value;
    }
    return modulated;
}

arma::Col<arma::cx_double> Signal::QAM16(QVector<bool> &dataArray)
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 4){
        double real = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray[i]) * (2 - (1 - dataArray[i+2]));
        double imag = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray[i + 1]) * (2 - (1 - dataArray[i+3])); 
        arma::cx_double value(real, imag);
        qDebug() << "QAM16 --> " << value.real() << value.imag();
        modulated << value;
    }
    return modulated;
}

arma::Col<arma::cx_double> Signal::QAM64(QVector<bool> &dataArray)
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 6){
        double real = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray[i]) * 
                                            (4 - (1 - 2 * dataArray[i+2])) * (2 - (1 - dataArray[i+4]));
        double imag = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray[i + 1]) * 
                                            (4 - (1 - 2 * dataArray[i+3])) * (2 - (1 - dataArray[i+5])); 
        arma::cx_double value(real, imag);
        qDebug() << "QAM64 --> " << value.real() << value.imag();
        modulated << value;
    }
    return modulated;
}

arma::Col<arma::cx_double> Signal::QAM256(QVector<bool> &dataArray)
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray.length(); i = i + 8){
        double real = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray[i]) * (8 - (1 - 2 * dataArray[i+2])) * 
                        (4 - (1 - 2 * dataArray[i+4])) * (2 - (1 - dataArray[i+6]));
        double imag = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray[i + 1]) * (8 - (1 - 2 * dataArray[i+3])) * 
                        (4 - (1 - 2 * dataArray[i+5])) * (2 - (1 - dataArray[i+7])); 
        arma::cx_double value(real, imag);
        qDebug() << "QAM256 --> " << value.real() << value.imag();
        modulated << value;
    }
    return modulated;
}


void Signal::demodulate(int modulationOrder, arma::Col<arma::cx_double> &IOvalues)
{
    // switch (modulationOrder)
    // {
    // case 2:
    //     modulatedIO_.append(QPSK(dataArray));
    //     //qDebug() << "modulateData --> " << modulatedIO_[0](0).real() << modulatedIO_[0](0).imag();
    //     break;
    // case 4:
    //     modulatedIO_.append(QAM16(dataArray));
    //     break;
    // case 6:
    //     modulatedIO_.append(QAM64(dataArray));
    //     break;
    // case 8:
    //     modulatedIO_.append(QAM256(dataArray));
    //     break;
    // }
}

QVector<bool> Signal::demQPSK(arma::Col<arma::cx_double> &IOvalues)
{
    QVector<bool> localData;

    return localData;
}

QVector<bool> Signal::demQAM16(arma::Col<arma::cx_double> &IOvalues)
{
    QVector<bool> localData;

    return localData;
}

QVector<bool> Signal::demQAM64(arma::Col<arma::cx_double> &IOvalues)
{
    QVector<bool> localData;

    return localData;
}

QVector<bool> Signal::demQAM256(arma::Col<arma::cx_double> &IOvalues)
{
    QVector<bool> localData;

    return localData;
}