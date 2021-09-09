#include "NetworkManager.h"
#include "src/equipment/Cell.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"

#include "src/debug.h"

#include <QVector>
#include <QRandomGenerator>

// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

NetworkManager::NetworkManager()
{
    cellContainer_ = new QVector<Cell*>;
    gNodeBContainer_ = new QVector<gNodeB*>;
    userEquipmentContainer_ = new QVector<UserEquipment*>;
}

NetworkManager::~NetworkManager()
{
    for (auto i : *cellContainer_) {
        delete i;
    }
    delete cellContainer_;
    for (auto i : *gNodeBContainer_)
    {
        delete i;
    }
    delete gNodeBContainer_;
    for (auto i : *userEquipmentContainer_)
    {
        delete i;
    }
    delete userEquipmentContainer_;
}

// ----- [ EQUIPMENT GENERATORS ] --------------------------------------------------------------------------------------

Cell* NetworkManager::createCell (int idCell)
{
    debug("NetworkManager: starting to create a cell.");
    Cell *cell = new Cell();
    cell->setEquipmentID(idCell);
    cell->setEquipmentType(Equipment::EquipmentType::TYPE_CELL);
    getCellContainer()->push_back(cell);

    return cell;
}

Cell* NetworkManager::createCell (int idCell, gNodeB *targetGNb)
{
    Cell *cell = new Cell();
    cell->setEquipmentID(idCell);
    cell->setEquipmentType(Equipment::EquipmentType::TYPE_CELL);
    cell->setTargetGNodeB(targetGNb);
    targetGNb->addCell(cell);
    getCellContainer()->push_back(cell);

    return cell;
}

gNodeB* NetworkManager::createGNodeB (int id, Cell *cell, double posX, double posY, double posZ)
{
    debug("Network Manager: Starting to create a gNb. ");
    gNodeB *gNb = new gNodeB(id, cell, posX, posY, posZ);
    getGNodeBContainer()->push_back(gNb);
    attachGNodeBtoCell(cell, gNb);
    return gNb;
}

gNodeB* NetworkManager::createGNodeB (int id, double posX, double posY, double posZ)
{
    debug("Network Manager: Starting to create a gNb. ");
    gNodeB *gNb = new gNodeB(id, posX, posY, posZ);
    getGNodeBContainer()->push_back(gNb);
    return gNb;
}

UserEquipment* NetworkManager::createUserEquipment (int id, 
                                                    double posX, double posY, double posZ, 
                                                    Cell *cell, gNodeB *targetGNodeB)
{
    UserEquipment *ue = new UserEquipment(id,
                                          posX, posY, posZ, cell, targetGNodeB,
                                          Mobility::Model::CONSTANT_POSITION);
    getUserEquipmentContainer()->push_back(ue);
    attachUEtoCell(cell, ue);
    return ue;
}

void NetworkManager::createMultipleUserEquipments(  int number, int borderID, int lowX, int highX, int lowY, int highY, 
                                                    int borderZ, Cell *cell, gNodeB *targetGNodeB )
{
    for (int i = 1; i <= number; i++) {
        int id = i + 10000;
        int posX = QRandomGenerator::global()->bounded(lowX, highX);
        int posY = QRandomGenerator::global()->bounded(lowY, highY);
        int posZ = QRandomGenerator::global()->bounded(1, borderZ);
        UserEquipment *ue = new UserEquipment(  id,
                                                posX, posY, posZ, cell, targetGNodeB,
                                                Mobility::Model::CONSTANT_POSITION);
        getUserEquipmentContainer()->push_back(ue);
        attachUEtoCell(cell, ue);
    }
}

void NetworkManager::attachUEtoCell(Cell *cell, UserEquipment *ue)
{
    getCellByID(cell->getEquipmentID())->attachUE(ue);
}

void NetworkManager::attachGNodeBtoCell(Cell *cell, gNodeB *gNb)
{
    getCellByID(cell->getEquipmentID())->setTargetGNodeB(gNb);
}

// ----- [ GETTERS\SETTERS ] -------------------------------------------------------------------------------------------

// Get containers
QVector<gNodeB*>* NetworkManager::getGNodeBContainer (void)
{
  return gNodeBContainer_;
}

QVector<Cell*>* NetworkManager::getCellContainer (void)
{
    return cellContainer_;
}

QVector<UserEquipment*>* NetworkManager::getUserEquipmentContainer (void)
{
    return userEquipmentContainer_;
}

// Get by ID
Cell* NetworkManager::getCellByID (int cellID)
{
    for (auto cell : *getCellContainer()) {
        if (cell->getEquipmentID() == cellID) {
            return cell;
        }
    }
    return nullptr;
}

gNodeB* NetworkManager::getGNodeBByID (int idGNodeB)
{
    for (auto gNodeB : *getGNodeBContainer()) {
        if (gNodeB->getEquipmentID() == idGNodeB) {
            return gNodeB;
        }
    }
    return nullptr;
}

gNodeB* NetworkManager::getGNodeBByCellID (int idCell)
{
    for (auto gNodeB : *getGNodeBContainer()) {
        // TODO: Check the correct methods...something could be OVERcoded...should be a simpiest way
        if (gNodeB->getCellByID(idCell)->getEquipmentID() == idCell) {
            return gNodeB;
        }
    }
    return nullptr;
}

UserEquipment* NetworkManager::getUserEquipmentByID (int idUE)
{
    for (auto userEquipment : *getUserEquipmentContainer()) {
        if (userEquipment->getEquipmentID() == idUE) {
            return userEquipment;
        }
    }
    return nullptr;
}

double NetworkManager::calcOnePointSINR()
{
    // TODO: Calculate
    if ( !userEquipmentContainer_->isEmpty() && !gNodeBContainer_->isEmpty() ) {
        qDebug() << "users and gnodeb are not empty";
    }
    return 1;
}

void NetworkManager::setWorkingTime(int time)
{
    currentTime_ = time;
}

int NetworkManager::getWorkingTime()
{
    return currentTime_;
}

void NetworkManager::decreaseTime()
{
    currentTime_--;
}

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------

// void NetworkManager::print()
// {
//     // for (auto gNodeB : *gNodeBContainer_) {
//     //     gNodeB->print();
//     // }

//     // for(auto ue : *userEquipmentContainer_) {
//     //     ue->print();
//     // }
// }



