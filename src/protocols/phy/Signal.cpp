#include "Signal.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QtMath>

// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

Signal::Signal()
{
    // powerValues_.resize(1);
}

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void Signal::setPowerValues(const QVector< QVector<double> > powerValues)
{
    powerValues_ = powerValues;
}

void Signal::setIOValues(const QVector< QVector<double> >  IOvalues)
{
    IOvalues_ = IOvalues;
}

QVector<QVector<double>> Signal::getPowerValues()
{
    return powerValues_;
}

QVector<QVector<double>> Signal::getIOValues()
{
    return IOvalues_;
}

// ----- [ FUNCTIONALITY ] ---------------------------------------------------------------------------------------------

Signal* Signal::copy(void)
{
    Signal *txSignal = new Signal();
    txSignal->setPowerValues(getPowerValues());
    txSignal->setIOValues(getIOValues());

    return txSignal;
}
