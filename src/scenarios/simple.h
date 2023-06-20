#pragma once

#include <QString>
#include <QQueue>

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/core/NetworkManager.h"
#include "src/core/Simulator.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/phy/Physical.h"

#include "src/debug.h"

static QVector<QVector<QPair<int, int>>> &Simple ()
{

    QGeoCoordinate leftBottom = {54.930053, 82.74078};
    QGeoCoordinate rightUp = {55.140901, 83.102854};

    NetworkManager *networkManager = new NetworkManager();
    networkManager->setWorkingTime(17);

    // Create gNodeB
    int idGNb = 2000;
    QGeoCoordinate gnb_01_pos = leftBottom.atDistanceAndAzimuth(600, 45);
    gNodeB *gNb_01 = networkManager->createGNodeB(idGNb, gnb_01_pos);
    int idCell = 0;
    Cell *cell_11 = networkManager->createCell(0, gNb_01, 100, 0);
    Cell *cell_12 = networkManager->createCell(1, gNb_01, 100, 120);
    Cell *cell_13 = networkManager->createCell(2, gNb_01, 100, 180);

    idGNb = 3000;
    QGeoCoordinate gnb_02_pos = leftBottom.atDistanceAndAzimuth(1200, 45);
    gNodeB *gNb_02 = networkManager->createGNodeB(idGNb, gnb_02_pos);
    Cell *cell_21 = networkManager->createCell(3, gNb_02, 100, 0);
    Cell *cell_22 = networkManager->createCell(4, gNb_02, 100, 120);
    Cell *cell_23 = networkManager->createCell(5, gNb_02, 100, 180);

    int nUe = 10;
    networkManager->createMultipleUserEquipments(nUe, 0, 1000, 0, 1000, 10, nullptr, nullptr);
    debug("Simple: User Equipments entity are created");

    networkManager->setSINRCalcMethod(NetworkManager::SINRCalcMethod::STUPID);
    networkManager->runNetwork();

    // ----- [ Debugging ] -------------------------------------------------------------------------------------------------
    if (DEBUGGING == false){
        qDebug() << "Network Manager:";

        qDebug() <<"    "<<"Cell IDs list";
        for(auto cell: *networkManager->getCellContainer()){
            qDebug() <<"        "<< "Cell id: " << cell->getEquipmentId();
            qDebug() <<"            "<<"Cell info:";
            qDebug() <<"            "<<"UE IDs list in CELL";
            for( auto ue: *cell->getUserEquipmentContainer() ){
                qDebug() <<"            "<< "UE id: " << ue->getEquipmentId();
                qDebug() <<"                "<< "Bearers:";
                for ( auto bearer: *ue->getBearerContainer() ) {
                    qDebug() <<"                "<< "5QI: " << bearer->getQoSProfile()->getId();
                }
            }
        }
        qDebug() <<"    "<<"gNodeB IDs list";
        for(auto gNb: *networkManager->getGNodeBContainer()){
            qDebug() <<"        "<< gNb->getEquipmentId();
        }

        qDebug() <<"    "<<"UE IDs list";
        for(auto ue: *networkManager->getUserEquipmentContainer()){
            qDebug() <<"        "<< ue->getEquipmentId();
        }
    }
    // TODO: Need to run a first simple simulation

    Simulator *simulator = new Simulator();
    simulator->setTime(1);
    simulator->run();

    QQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    for(auto q : queue){
        qDebug() << q;
        //queue.dequeue();
        queue.enqueue(2);
    }
    qDebug() <<"-->";
    for(auto q : queue){
        qDebug() << q;
    }

    return cell_11->getAllData();
}

//git push test
