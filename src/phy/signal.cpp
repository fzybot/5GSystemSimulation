#include "signal.h"
#include <QRandomGenerator>
Signal::Signal()
{

}

void Signal::setPowerValues(QVector<QVector<double>> amplitudes){

    m_powerValues = amplitudes;
}

QVector< QVector<double> > Signal::getPowerValues(){

    return m_powerValues;
}

void Signal::setPhases(QVector<QVector<double>> phases){

    m_phases = phases;
}

QVector< QVector<double> > Signal::getPhases(){

    return m_phases;
}

void Signal::generateRandomPhases(int MIMOSize, int dataSize){
//    m_powerValues.resize(MIMOSize);
//    for (int i = 0; i < size; i++){
//        double mimo_1_ampl = QRandomGenerator::global()->generateDouble();
//        m_powerValues.push_back();
//    }
}

