#pragma once


#include "src/equipment/Equipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Walker.h"
#include "src/protocols/phy/propagationModels.h"
#include "src/simulation/Simulation.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/phy/Signal.h"
#include "src/equipment/antenna/AntennaArray.h"

#include <QDebug>


static void simpleTest()
{
//    gNodeB bs1;
//    qDebug() << bs1.PCI << bs1.bandwidth << "Number of BS: " << bs1.dataSize;
//    Simulation sim1;
//    qDebug() <<"Path Loss:" << sim1.calculatePathLoss(100, 0);
//    qDebug() <<"SINR:" << sim1.userEqipmnets[0].SINR;
    /*
    for (int i = 0; i < sim1.userEqipmnets.length(); ++i){
        qDebug() <<"SINR:" << sim1.userEqipmnets[i].SINR;
        qDebug() << "Step size:" << sim1.userEqipmnets[i].speed;
        qDebug() << "Step size:" << sim1.userEqipmnets[i].stepSize;
        qDebug() << "Longtitude: " << sim1.userEqipmnets[i].longtitude;
        qDebug() << "Latitude: "<< sim1.userEqipmnets[i].latitude;
        qDebug() <<"---------------------------------";
   }
   */
//    sim1.showBordersll();


    //**************************************************************
    // Bandwidth class test
    //**************************************************************
    // Bandwidth band("FR1", "n1", 15, 10, 20, 0, 0, false);
    // band.print();
    // qDebug() << PRBs_for_BW["FR2"][60][100];


    //**************************************************************
    // Signal class tests
    //**************************************************************

    AntennaArray ant1;
    ant1.calculateElevationGrid();
    ant1.calculateAzimuthGrid();
    ant1.showAzimuthGrid();
    ant1.showElevationGrid();
}
