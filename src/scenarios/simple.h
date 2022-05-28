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
    NetworkManager *networkManager = new NetworkManager();
    RadioChannel *channel = new RadioChannel();
    networkManager->setWorkingTime(17);

    // Create Cell
    int idCell = 0;
    int posX = 500;
    int posY = 500;
    int posZ = 50;
    Cell *cell = networkManager->createCell(idCell, posX, posY, posZ);
    cell->getPhyEntity()->configNewBandwidth("FR1", "n3", NUMEROLOGY[0], 10, 50, 0, 0, true);
    cell->getPhyEntity()->configNewBandwidth("FR1", "n8", NUMEROLOGY[0], 10, 50, 0, 0, true);

    // int idCell_01 = 1;
    // int posX_01 = 200;
    // int posY_01 = 200;
    // int posZ_01 = 50;
    // Cell *cell_01 = networkManager->createCell(idCell_01);

    // Create gNodeB
    int idGNb = 1000;
    gNodeB *gNb = networkManager->createGNodeB(idGNb, cell, posX, posY, posZ);
    //gNb->addCell(cell_01);
    debug("Simple: gNodeB entity is created");
    channel->addDevice(gNb);

    // Create User Equipment
    int idUE = 2;
    int posX_ue = 2000;
    int posY_ue = 500;
    double posZ_ue = 1.5;
    UserEquipment *ue = networkManager->createUserEquipment(idUE, posX_ue, posY_ue, posZ_ue, cell, gNb);
    //ue->getPhyEntity()->configNewBandwidth("FR1", "n3", NUMEROLOGY[0], 10, 50, 0, 0, true);
    channel->addDevice(ue);

    // int idUE2 = 3;
    // int posX_ue2 = 0;
    // int posY_ue2 = 500;
    // double posZ_ue2 = 1.5;
    // UserEquipment *ue2 = networkManager->createUserEquipment(idUE2, posX_ue2, posY_ue2, posZ_ue2, cell, gNb);
    // channel->addDevice(ue2);

    int nUe = 10;
    networkManager->createMultipleUserEquipments(nUe, 0, 1000, 0, 1000, 10, cell, gNb);
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

    for (auto prb: cell->getPrbUtilized()){
        qDebug() <<"PRB UTILIZED --> "<< prb;
    }

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

    return cell->getAllData();
}

//git push test
