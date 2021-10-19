#pragma once

#include <QString>

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/core/NetworkManager.h"
#include "src/core/Simulator.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/protocols/bearers/RadioBearer.h"

#include "src/debug.h"

static void Simple ()
{
    NetworkManager *networkManager = new NetworkManager();
    RadioChannel *channel = new RadioChannel();
    networkManager->setWorkingTime(17);

    // Create Cell
    int idCell = 0;
    int posX = 100;
    int posY = 100;
    int posZ = 50;
    Cell *cell = networkManager->createCell(idCell);
    int idCell_01 = 1;
    int posX_01 = 200;
    int posY_01 = 200;
    int posZ_01 = 50;
    Cell *cell_01 = networkManager->createCell(idCell_01);

    // Create gNodeB
    int idGNb = 1000;
    gNodeB *gNb = networkManager->createGNodeB(idGNb, cell, posX, posY, posZ);
    gNb->addCell(cell_01);
    debug("Simple: gNodeB entity is created");
    channel->addDevice(gNb);

    // Create User Equipment
    // int idUE = 2;
    // int posX_ue = 120;
    // int posY_ue = 130;
    // double posZ_ue = 1.5;
    // UserEquipment *ue = networkManager->createUserEquipment(idUE, posX_ue, posY_ue, posZ_ue, cell, gNb);
    // channel->addDevice(ue);

    networkManager->createMultipleUserEquipments(2, 0, 200, 0, 1000, 100, cell, gNb);
    networkManager->createMultipleUserEquipments(2, 0, 200, 0, 1000, 100, cell_01, gNb);
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
}
