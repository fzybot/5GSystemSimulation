#include "signal.h"
#include <QRandomGenerator>
#include <QDebug>


Signal::Signal()
{

}

void Signal::setPowerValues(QVector<QVector<double>> amplitudes){

    m_powerValues = amplitudes;
}

QVector< QVector<double> > Signal::getPowerValues(){

    return m_powerValues;
}

void Signal::setIOValues(QVector<QVector<double>> phases){

    m_IOvalues = phases;
}

QVector< QVector<double> > Signal::getIOValues(){

    return m_IOvalues;
}

void Signal::prindIOValues(){
    for(int i = 0; i < m_powerValues.size(); i++){
        qDebug() << "MIMO index = " << i << Qt::endl;
        for(int j = 0; j < m_powerValues[i].size(); j++){
            qDebug() << "Value = " << m_powerValues[i][j] << Qt::endl;
        }
    }
}

void Signal::generateRandomIOValues(int MIMOSize, int dataSize){
    m_powerValues.resize(MIMOSize);
    for (int i = 0; i < MIMOSize; i++){
        for(int j = 0; j < dataSize; j++){
            double mimoPower = QRandomGenerator::global()->generateDouble();
            m_powerValues[i].append(mimoPower);
        }
    }
}

