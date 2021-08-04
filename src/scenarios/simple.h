#pragma once

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/core/NetworkManager.h"

#include <QDebug>

static const bool DEBUGGING = true;

static void Simple ()
{
    qDebug() << "Simple Hello world!";
    NetworkManager *networkManager = new NetworkManager();
    qDebug() << "Network manager is crated";

    // Create Cell
    int idCell = 0;
    int posX = 100;
    int posY = 100;
    int posZ = 50;
    Cell *cell = networkManager->createCell(idCell);
    if (DEBUGGING == true) {
        qDebug() << "Cell entity is created";
    }

    // Create gNodeB
    int idGNb = 1;
    //gNodeB *gNb = networkManager->createGNodeB(idGNb, cell, posX, posY, posZ);
    qDebug() << "gNodeB entity is   created";

    // Create User Equipment
    int idUE = 2;
    int posX_ue = 120;
    int posY_ue = 130;
    double posZ_ue = 1.5;
    //UserEquipment *ue = networkManager->createUserEquipment(idUE, posX_ue, posY_ue, posZ_ue, cell, gNb);
    //qDebug() << "User Equipment entity is created";
}
