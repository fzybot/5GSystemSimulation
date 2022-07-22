#pragma once

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/core/NetworkManager.h"

#include "calculus_test.h"
#include "packet_test.h"
#include <fftw3.h>>

void angleTest(){
    NetworkManager *networkManager = new NetworkManager();
    networkManager->setWorkingTime(17);

    // Create Cell
    int idCell = 0;
    int posX = 100;
    int posY = 100;
    int posZ = 50;
    Cell *cell = networkManager->createCell(idCell, posX, posY, posZ);

    // Create gNodeB
    int idGNb = 1000;
    gNodeB *gNb = networkManager->createGNodeB(idGNb, cell, posX, posY, posZ);

    // Create User Equipment
    int idUE = 2;
    QVector<int> posX_ue = {150, 150, 125, 100, 75,   50,  50, 50, 75, 100, 175, 150};
    QVector<int> posY_ue = {100, 125, 150, 150, 150, 125, 100, 75, 50,  50,  50,  75};
    double posZ_ue = 1.5;
    UserEquipment *ue0 = networkManager->createUserEquipment(idUE, posX_ue[0], posY_ue[0], posZ_ue, cell, gNb);
    UserEquipment *ue1 = networkManager->createUserEquipment(idUE, posX_ue[1], posY_ue[1], posZ_ue, cell, gNb);
    UserEquipment *ue2 = networkManager->createUserEquipment(idUE, posX_ue[2], posY_ue[2], posZ_ue, cell, gNb);
    UserEquipment *ue3 = networkManager->createUserEquipment(idUE, posX_ue[3], posY_ue[3], posZ_ue, cell, gNb);
    UserEquipment *ue4 = networkManager->createUserEquipment(idUE, posX_ue[4], posY_ue[4], posZ_ue, cell, gNb);
    UserEquipment *ue5 = networkManager->createUserEquipment(idUE, posX_ue[5], posY_ue[5], posZ_ue, cell, gNb);
    UserEquipment *ue6 = networkManager->createUserEquipment(idUE, posX_ue[6], posY_ue[6], posZ_ue, cell, gNb);
    UserEquipment *ue7 = networkManager->createUserEquipment(idUE, posX_ue[7], posY_ue[7], posZ_ue, cell, gNb);
    UserEquipment *ue8 = networkManager->createUserEquipment(idUE, posX_ue[8], posY_ue[8], posZ_ue, cell, gNb);
    UserEquipment *ue9 = networkManager->createUserEquipment(idUE, posX_ue[9], posY_ue[9], posZ_ue, cell, gNb);
    UserEquipment *ue10 = networkManager->createUserEquipment(idUE, posX_ue[10], posY_ue[10], posZ_ue, cell, gNb);
    UserEquipment *ue11 = networkManager->createUserEquipment(idUE, posX_ue[11], posY_ue[11], posZ_ue, cell, gNb);

    qDebug() << "length: " << networkManager->getUserEquipmentContainer()[0].length();
    for (int i = 0; i < networkManager->getUserEquipmentContainer()[0].length(); i++)
    {
        qDebug() << "Ange test: " << i << " " << cell->calculateAngeToUserEquipmentRad(networkManager->getUserEquipmentContainer()[0][i]);
    }
}

void test_passing(){
    test_sum_dbm();
    vectorTest();
    angleTest();
}
