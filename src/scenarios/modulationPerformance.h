#pragma once

#include "src/equipment/Equipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Walker.h"
#include "src/protocols/phy/propagationModels.h"
#include "src/simulation/Simulation.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/phy/Symbol.h"
#include "src/equipment/antenna/AntennaArray.h"
#include "src/visualization/Chartable.h"

#include <armadillo>

#include <QDebug>
#include <QPair>
#include <QFile>
#include <QTextStream>


#define NUMBER_OF_REP 1000



QVector<QVector<QPair<float, float>>>   dopplerModulationPerformanceTest(
                                        int modulationOrder, int speedLow, int speedHigh, 
                                        int speedStep, int centralFrequency, int scs, int bw
                                        )
{

    QFile file("/home/ruslan/dev/git/5GSystemSimulation/FeatureTesting/modulation.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream stream( &file );
    
    

    QVector<QVector<QPair<float, float>>> localData;
    QVector<QPair<float, float>> dataEvm, dataBer;


    Symbol symbol(centralFrequency, scs, bw);

    for (int speed = speedLow; speed < speedHigh; speed = speed + speedStep)
    {
        QPair<float, float> pairEvm, pairBer;

        symbol.transmitAndReceive(modulationOrder, speed);
        //qDebug() << "Doppler freq -> " << symbol.getDopplerFreq();

        pairEvm.first = speed;
        pairEvm.second = symbol.getAverageEvm();
        dataEvm.push_back(pairEvm);
        
        

        pairBer.first = speed;
        pairBer.second = symbol.getBER()[0];
        dataBer.push_back(pairBer);

        stream  << QString::number(speed) << " " << QString::number(symbol.getAverageEvm()) << " " 
                << QString::number(symbol.getBER()[0]) << endl;
    }

    localData.push_back(dataEvm);
    localData.push_back(dataBer);

    file.close();
    

    return localData;
}