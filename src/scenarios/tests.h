#ifndef TESTS_H
#define TESTS_H

#include <QDebug>

#include <src/equipment/equipment.h>
#include <src/equipment/gNodeB.h>
#include <src/equipment/user_equipment.h>
#include <src/equipment/walker.h>
#include <src/phy/propagation_models.h>
#include <src/simulation/simulation.h>
#include <src/phy/Channel/bandwidth.h>
#include <src/phy/signal.h>



static void simpleTest(){

    gNodeB bs1;
    qDebug() << bs1.PCI << bs1.bandwidth << "Number of BS: " << bs1.dataSize;
//  bs1.printData();
    Simulation sim1;
    qDebug() <<"Path Loss:" << sim1.calculatePathLoss(100, 0);
    qDebug() <<"SINR:" << sim1.userEqipmnets[0].SINR;
//    for (int i = 0; i < sim1.userEqipmnets.length(); i ++){
//        qDebug() <<"SINR:" << sim1.userEqipmnets[i].SINR;
//        qDebug() << "Step size:" << sim1.userEqipmnets[i].speed;
//        qDebug() << "Step size:" << sim1.userEqipmnets[i].stepSize;
//        qDebug() << "Longtitude: " << sim1.userEqipmnets[i].longtitude;
//        qDebug() << "Latitude: "<< sim1.userEqipmnets[i].latitude;
//        qDebug() <<"---------------------------------";
//    }
    sim1.showBordersll();

    //**************************************************************
    // Bandwidth class test
    //**************************************************************
    Bandwidth band("FR1", "n1", 15, 10, 20, 0, 0, false);
    band.print();
    qDebug() << PRBs_for_BW["FR2"][60][100];


    //**************************************************************
    // Signal class tests
    //**************************************************************
    Signal sig_1;
    sig_1.generateRandomIOValues(2, 10);
    sig_1.prindIOValues();

}

#endif // TESTS_H
