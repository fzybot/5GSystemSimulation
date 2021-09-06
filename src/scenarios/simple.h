#pragma once

#include <QString>

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/core/NetworkManager.h"
#include "src/core/Simulator.h"
#include "src/protocols/phy/Channel/RadioChannel.h"

#include "src/debug.h"

static void Simple ()
{
    NetworkManager *networkManager = new NetworkManager();
    RadioChannel *channel = new RadioChannel();

    // Create Cell
    int idCell = 0;
    int posX = 100;
    int posY = 100;
    int posZ = 50;
    Cell *cell = networkManager->createCell(idCell);

    // Create gNodeB
    int idGNb = 1000;
    gNodeB *gNb = networkManager->createGNodeB(idGNb, cell, posX, posY, posZ);
    debug("Simple: gNodeB entity is created");
    channel->addDevice(gNb);

    // Create User Equipment
    int idUE = 2;
    int posX_ue = 120;
    int posY_ue = 130;
    double posZ_ue = 1.5;
    UserEquipment *ue = networkManager->createUserEquipment(idUE, posX_ue, posY_ue, posZ_ue, cell, gNb);
    
    debug("Simple: User Equipment entity is created");
    channel->addDevice(ue);




// ----- [ Debugging ] -------------------------------------------------------------------------------------------------
    if (DEBUGGING == true){
        qDebug() << "Network Manager:";

        qDebug() <<"    "<<"Cell IDs list";
        for(auto cell: *networkManager->getCellContainer()){
            qDebug() <<"        "<< cell->getEquipmentID();
            qDebug() <<"        "<<"Cell info:";
            qDebug() <<"            "<<cell;
        }


        qDebug() <<"    "<<"gNodeB IDs list";
        for(auto gNb: *networkManager->getGNodeBContainer()){
            qDebug() <<"        "<< gNb->getEquipmentID();
        }

        qDebug() <<"    "<<"UE IDs list";
        for(auto ue: *networkManager->getUserEquipmentContainer()){
            qDebug() <<"        "<< ue->getEquipmentID();
        }
    }
    // TODO: Need to run a first simple simulation

    Simulator *simulator = new Simulator();
    simulator->setTime(100);
    simulator->run();
}
