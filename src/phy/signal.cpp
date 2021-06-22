#include "Signal.h"

#include <QDebug>
#include <QRandomGenerator>


Signal::Signal() :
    sampleRate(0),
    powerValues(),
    IOvalues()
{ }

void Signal::setPowerValues(const QVector<QVector<double>>& powerValues)
{
    this->powerValues = powerValues;
}
void Signal::setIOValues(const QVector<QVector<double>>& IOvalues) {

    this->IOvalues = IOvalues;
}

QVector<QVector<double>> Signal::getPowerValues() const
{
    return powerValues;
}
QVector<QVector<double>> Signal::getIOValues() const
{
    return IOvalues;
}

void Signal::prindIOValues() const
{
    for(int i = 0; i < powerValues.size(); ++i) {
        qDebug() << "MIMO index = " << i << Qt::endl;
        for(auto& value : powerValues[i]) {
            qDebug() << "Value = " << value << Qt::endl;
        }
    }
}
void Signal::generateRandomIOValues(int MIMOSize, int dataSize)
{
    powerValues.resize(MIMOSize);
    for (auto& values : powerValues) {
        values.resize(dataSize);
        for(auto& value : values) {
            value = QRandomGenerator::global()->generateDouble();
        }
    }
}
