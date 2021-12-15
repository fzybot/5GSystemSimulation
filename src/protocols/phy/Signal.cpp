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

void Signal::setIOValues(const QVector< QVector<QPair<float, float>> >  IOvalues)
{
    IOvalues_ = IOvalues;
}

QVector<QVector<double>> &Signal::getPowerValues()
{
    return powerValues_;
}

QVector<QVector<QPair<float, float>>> &Signal::getIOValues()
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
