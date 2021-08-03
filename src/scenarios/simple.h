#pragma once

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/protocols/phy/Signal.h"
#include "src/core/NetworkManager.h"

static void Simple ()
{
    NetworkManager *networkManager = new NetworkManager();

    // Create Cell
    int idCell = 0;
    int posX = 100;
    int posY = 100;
    int posZ = 50;
    Cell *cell = networkManager->createCell(idCell);

    // Create gNodeB
    int idGNb = 1;
    gNodeB *gNb = networkManager->createGnodeB(idGNb, cell, posX, posY, posZ);

    // Create User Equipment
    int idUE = 2;
    int posX_ue = 120;
    int posY_ue = 130;
    double posZ_ue = 1.5;
    UserEquipment *ue = networkManager->createUserEquipment(idUE, posX_ue, posY_ue, posZ_ue, cell, gNb);

    networkManager->print();
}