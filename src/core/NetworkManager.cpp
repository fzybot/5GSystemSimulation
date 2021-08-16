#include "NetworkManager.h"
#include "src/equipment/Cell.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"

#include "src/debug.h"

#include <QVector>

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
    cell->setEquipmentType(Equipment::TYPE_CELL);
    getCellContainer()->push_back(cell);

    return cell;
}

gNodeB* NetworkManager::createGNodeB (int id, Cell *cell, double posX, double posY, double posZ)
{
    debug("Network Manager: Starting to create a gNb. ");
    gNodeB *gNb = new gNodeB(id, cell, posX, posY, posZ);
    getGNodeBContainer()->push_back(gNb);
    return gNb;
}

UserEquipment* NetworkManager::createUserEquipment (int id, 
                                                    double posX, double posY, double posZ, 
                                                    Cell *cell, gNodeB *targetGNodeB)
{
    UserEquipment *ue = new UserEquipment(id,
                                          posX, posY, posZ, cell, targetGNodeB,
                                          Mobility::CONSTANT_POSITION);
    getUserEquipmentContainer()->push_back(ue);
    return ue;
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



