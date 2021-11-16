#include "NetworkManager.h"
#include "src/equipment/Cell.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"
#include "src/protocols/mac_layer/CellMacEntity.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/equipment/mobility/ConstantPosition.h"

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
    cell->setEquipmentId(idCell);
    cell->setEquipmentType(Equipment::EquipmentType::TYPE_CELL);
    cell->setLinkBudgetParameters();
    getCellContainer()->push_back(cell);

    return cell;
}

Cell* NetworkManager::createCell (int idCell, double posX, double posY, double posZ)
{
    debug("NetworkManager: starting to create a cell.");
    Cell *cell = new Cell();
    cell->setEquipmentId(idCell);
    cell->setEquipmentType(Equipment::EquipmentType::TYPE_CELL);
    cell->setLinkBudgetParameters();
    CartesianCoordinates *position = new CartesianCoordinates(posX, posY, posZ);
    Mobility *m = new ConstantPosition();
    m->setPosition(position);
    cell->setMobilityModel(m);
    // Becouse in Mobility class a new object is created
    delete position;

    getCellContainer()->push_back(cell);

    return cell;
}

Cell* NetworkManager::createCell (int idCell, gNodeB *targetGNb)
{
    Cell *cell = new Cell();
    cell->setEquipmentId(idCell);
    cell->setEquipmentType(Equipment::EquipmentType::TYPE_CELL);
    cell->setLinkBudgetParameters();
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
    //attachUEtoCell(cell, ue);
    return ue;
}

void NetworkManager::createMultipleUserEquipments(  int number, int lowX, int highX, int lowY, int highY, 
                                                    int borderZ, Cell *cell, gNodeB *targetGNodeB )
{
    for (int i = 1; i <= number; i++) {
        ueIdLocal_ += 1;
        int posX = QRandomGenerator::global()->bounded(lowX, highX);
        int posY = QRandomGenerator::global()->bounded(lowY, highY);
        int posZ = 2;
        UserEquipment *ue = new UserEquipment(ueIdLocal_,
                                              posX, posY, posZ, nullptr, targetGNodeB,
                                              Mobility::Model::CONSTANT_POSITION);
        getUserEquipmentContainer()->push_back(ue);
        //attachUEtoCell(cell, ue);
    }
}

void NetworkManager::attachUEtoCell(Cell *cell, UserEquipment *ue)
{
    cell->attachUE(ue);
    deleteUeFromOtherCells(cell, ue);
}

void NetworkManager::deleteUeFromOtherCells(Cell *targetCell, UserEquipment *targetUe)
{
    for(auto cell: *getCellContainer()) {
        if ( cell != targetCell) {
            int neededIndex = 0;
            int localIdex = 0;
            for (auto ue: *cell->getUserEquipmentContainer()){
                if (ue == targetUe) {
                    neededIndex = localIdex;
                    break;
                }
                localIdex++;
            }
            cell->getUserEquipmentContainer()->remove(neededIndex);
        }
    }
}

void NetworkManager::attachGNodeBtoCell(Cell *cell, gNodeB *gNb)
{
    getCellByID(cell->getEquipmentId())->setTargetGNodeB(gNb);
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
        if (cell->getEquipmentId() == cellID) {
            return cell;
        }
    }
    return nullptr;
}

gNodeB* NetworkManager::getGNodeBByID (int idGNodeB)
{
    for (auto gNodeB : *getGNodeBContainer()) {
        if (gNodeB->getEquipmentId() == idGNodeB) {
            return gNodeB;
        }
    }
    return nullptr;
}

gNodeB* NetworkManager::getGNodeBByCellID (int idCell)
{
    for (auto gNodeB : *getGNodeBContainer()) {
        // TODO: Check the correct methods...something could be OVERcoded...should be a simpiest way
        if (gNodeB->getCellByID(idCell)->getEquipmentId() == idCell) {
            return gNodeB;
        }
    }
    return nullptr;
}

void NetworkManager::setSINRCalcMethod(NetworkManager::SINRCalcMethod method)
{
    methodSINR_ = method;
}

NetworkManager::SINRCalcMethod NetworkManager::getSINRCalcMethod()
{
    return methodSINR_;
}

// ----- [ EQUIPMENT GENERATORS ] --------------------------------------------------------------------------------------

UserEquipment* NetworkManager::getUserEquipmentByID (int idUE)
{
    for (auto userEquipment : *getUserEquipmentContainer()) {
        if (userEquipment->getEquipmentId() == idUE) {
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
    workit120TimeSlot_ =  time;
    current120TimeSlot_ = 0;
}

int &NetworkManager::getCurrentTime()
{
    return current120TimeSlot_;
}

int &NetworkManager::getWorkingTime()
{
    return workit120TimeSlot_;
}

void NetworkManager::increaseCurrentTime()
{
    current120TimeSlot_ = current120TimeSlot_ + 1;
}
// ----- [ SIMULATION ] ------------------------------------------------------------------------------------------------

void NetworkManager::runNetwork()
{
    while(getCurrentTime() != getWorkingTime()) {
        qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
        qDebug() << "Current 120 Time Slot ->" << getCurrentTime();
        // Calculate SINR for each Equipment
        calculateSINRPerEquipment(methodSINR_);
        assingUes(getCurrentTime());
        scheduleGNodeB();
        increaseCurrentTime();
    }
}

// TODO: Here we could make parallel calculations!!! Threads, etc.
void NetworkManager::scheduleGNodeB()
{
    for ( auto gNb: *getGNodeBContainer() ) {
        gNb->sync120TimeSlot(current120TimeSlot_);
        qDebug() << "gNodeB local 120 Time Slot --> " << gNb->getLocalSystem120TimeSlot();
        scheduleCells(gNb->getCellContainer());
    }
}

// TODO: Here we could make parallel calculations!!! Threads, etc.
void NetworkManager::scheduleCells(QVector<Cell*> *cellContainer)
{
    for (auto cell: *cellContainer) {

        cell->sync120TimeSlot(current120TimeSlot_);
        generateTrafficPerUE(cell->getUserEquipmentContainer());

        // TODO: somehow fix the loop
//        for (auto ue : *cell->getUserEquipmentContainer()) {
//            cell->getMacEntity()->packetsToTransportBlockContainer(ue->getPacketsContainer());
//        }
        // TODO: need some fix in order to schedule multiple bandwidth with differens SCS
        int scs = cell->getPhyEntity()->getBandwidthContainer()[0][0]->getSCS();
        if ( cell->getLocalSystem120TimeSlot() % (int)(120 / scs) == 0 ) {
            qDebug() << cell->getLocalSystem120TimeSlot() % (int)(120 / scs);
            qDebug() << "NetworkManager::scheduleCells:: cell SCS --> " << scs;
            qDebug() << "NetworkManager::scheduleCells:: cell time slot --> " << (int)cell->getLocalSystem120TimeSlot() / (int)(120/scs);
            cell->syncOwnTimeSlot((int) current120TimeSlot_ / (int)(120/scs));
            cell->getMacEntity()->schedule(cell);
        }
    }
}

void NetworkManager::generateTrafficPerUE(QVector<UserEquipment*> *ueContainer)
{
    for (auto ue: *ueContainer) {
        ue->generatePacketsPerBearer();
    }
}

bool NetworkManager::checkHandOver()
{
    return false;
}

void NetworkManager::makeHandOver()
{
    qDebug() << "Hand Over in progress...";

}

void NetworkManager::assingUes(int slot)
{
    double distance;
    double pathLos;
    double rssi;
    double rsrp;

    qDebug() << "NetworkManager::initialAttach()";
    for (auto ue: *getUserEquipmentContainer()) {
        int localIndex = 0;
        int neededIndex = -1;
        double max = -1000;
        if (ue->getSlotToCamp() == slot){
            for (auto cell : *getCellContainer()) {
                distance = ue->calculateDistanceToCell(cell);
                pathLos = ue->calculatePathLosToCell(cell, distance);
                rssi = ue->calculateRssiFromCell(cell, pathLos);
                rsrp = ue->calculateRsrpFromRssi(rssi);
                if ( (rsrp > max) && (rsrp >= -120) ) {
                    max = rsrp;
                    neededIndex = localIndex;
                }
                localIndex++;

                qDebug() << "NetworkManager::initialAttach() UE ID-->" << ue->getEquipmentId();
                qDebug() << "NetworkManager::initialAttach() Disnance to cell-->" << distance;
                qDebug() << "NetworkManager::initialAttach() Path Losses to cell-->" << pathLos;
                qDebug() << "NetworkManager::initialAttach() Cell EIRP-->" << cell->getEirp();
                qDebug() << "NetworkManager::initialAttach() RSSI-->" << rssi;
                qDebug() << "NetworkManager::initialAttach() RSRP-->" << rsrp;
            }
            if (neededIndex != -1) {
                ue->setTargetCell(getCellContainer()[0][neededIndex]);
                attachUEtoCell(ue->getTargetCell(), ue);
            }
        }
    }
}

float NetworkManager::calculatePathLosses(Cell *cell, UserEquipment *user)
{
    float pathLosses = 0;

    return pathLosses;
}

float NetworkManager::calculatePathLosses(UserEquipment *user1, UserEquipment *user2)
{
    float pathLosses = 0;
    
    return pathLosses;
}

void NetworkManager::calculateSINRPerEquipment(NetworkManager::SINRCalcMethod method)
{
    switch (method)
    {
    case NetworkManager::SINRCalcMethod::STUPID:
        calculateSINRPerEquipment_stupid();
        break;
    case NetworkManager::SINRCalcMethod::SIGNAL:
        calculateSINRPerEquipment_signals();
        break;
    case NetworkManager::SINRCalcMethod::SIGNAL_DOPPLER:
        calculateSINRPerEquipment_signal_doppler();
        break;
    default:
        break;
    } 
}

void NetworkManager::calculateSINRPerEquipment_stupid()
{
    float sinr;
    float pathLosses; // in [dBm]

    for ( auto ue : *getUserEquipmentContainer() ) {
        for ( auto cell: *getCellContainer() ) {
            
        }
    }
}

void NetworkManager::calculateSINRPerEquipment_signals()
{
    float sinr;
}

void NetworkManager::calculateSINRPerEquipment_signal_doppler()
{
    float sinr;
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



