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


void Signal::modulateData(int modulationOrder)
{
    switch (modulationOrder)
    {
    case 2:
        modulatedIO_.append(QPSK());
        //qDebug() << "modulateData --> " << modulatedIO_[0](0).real() << modulatedIO_[0](0).imag();
        break;
    case 4:
        modulatedIO_.append(QAM16());
        break;
    case 6:
        modulatedIO_.append(QAM64());
        break;
    case 8:
        modulatedIO_.append(QAM256());
        break;
    }
}

arma::Col<arma::cx_double> Signal::QPSK()
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray_.length(); i = i + 2){
        double real = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray_[i]);
        double imag = static_cast<double>(1 / qSqrt(2)) * (1 - 2 * dataArray_[i + 1]);
        arma::cx_double value(real, imag);
        qDebug() << "QPSK --> " << value.real() << value.imag();
        modulated << value;
    }
    return modulated;
}

arma::Col<arma::cx_double> Signal::QAM16()
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray_.length(); i = i + 4){
        double real = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray_[i]) * (2 - (1 - dataArray_[i+2]));
        double imag = static_cast<double>(1 / qSqrt(10)) * (1 - 2 * dataArray_[i + 1]) * (2 - (1 - dataArray_[i+3])); 
        arma::cx_double value(real, imag);
        qDebug() << "QAM16 --> " << value.real() << value.imag();
        modulated << value;
    }
    return modulated;
}

arma::Col<arma::cx_double> Signal::QAM64()
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray_.length(); i = i + 6){
        double real = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray_[i]) * 
                                            (4 - (1 - 2 * dataArray_[i+2])) * (2 - (1 - dataArray_[i+4]));
        double imag = static_cast<double>(1 / qSqrt(42)) * (1 - 2 * dataArray_[i + 1]) * 
                                            (4 - (1 - 2 * dataArray_[i+3])) * (2 - (1 - dataArray_[i+5])); 
        arma::cx_double value(real, imag);
        qDebug() << "QAM64 --> " << value.real() << value.imag();
        modulated << value;
    }
    return modulated;
}

arma::Col<arma::cx_double> Signal::QAM256()
{
    arma::Col<arma::cx_double> modulated;
    for (int i = 0; i < dataArray_.length(); i = i + 8){
        double real = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray_[i]) * (8 - (1 - 2 * dataArray_[i+2])) * 
                        (4 - (1 - 2 * dataArray_[i+4])) * (2 - (1 - dataArray_[i+6]));
        double imag = static_cast<double>(1 / qSqrt(170)) * (1 - 2 * dataArray_[i + 1]) * (8 - (1 - 2 * dataArray_[i+3])) * 
                        (4 - (1 - 2 * dataArray_[i+5])) * (2 - (1 - dataArray_[i+7])); 
        arma::cx_double value(real, imag);
        qDebug() << "QAM256 --> " << value.real() << value.imag() << static_cast<double>(1 / qSqrt(170));
        modulated << value;
    }
    return modulated;
}
