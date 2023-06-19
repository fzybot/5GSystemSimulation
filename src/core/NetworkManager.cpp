#include "NetworkManager.h"
#include "src/equipment/Cell.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/antenna/AntennaArray.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"
#include "src/protocols/mac_layer/CellMacEntity.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Bandwidth.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/equipment/mobility/ConstantPosition.h"
#include "src/additionalCalculations.h"
#include "src/protocols/phy/Channel/PropagationLossModel.h"
#include "src/commonParameters.h"
#include "src/equipment/antenna/Beam.h"

#include "src/debug.h"

#include <QVector>
#include <QRandomGenerator>
#include <QGeoCoordinate>

// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

NetworkManager::NetworkManager()
{
    cellContainer_ = new QVector<Cell*>;
    gNodeBContainer_ = new QVector<gNodeB*>;
    userEquipmentContainer_ = new QVector<UserEquipment*>;
    createRadioChannel();
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

Cell* NetworkManager::createCell (int idCell, CartesianCoordinates *position, double alt, double dist, double angle, double azimuth)
{
    qDebug() << "NetworkManager: starting to create a cell.";
    Cell *cell = new Cell();
    qDebug() << "new cell.";
    cell->setEquipmentId(idCell);
    cell->setEquipmentType(Equipment::EquipmentType::TYPE_CELL);
    cell->setLinkBudgetParameters();
    
    Mobility *m = new ConstantPosition();
    QGeoCoordinate coordinates = _leftBottom.atDistanceAndAzimuth(dist, angle);
    coordinates.setAltitude(alt);
    position->setCoordintes(coordinates);
    position->setAzimuth(azimuth);
    m->setPosition(position);
    cell->setMobilityModel(m);

    cell->setPropagationModel(new PropagationLossModel(PropagationLossModel::PropagationModel::UMA_NLOS));
    qDebug() << "Add antenna array to cell.";

    double azim = cell->getPosition()->getAzimuth();
    double elevation = cell->getPosition()->getAltitude();
    cell->addAntennaArray(AntennaArray::AntennaType::ANTENNA_TYPE_3GPP_CUSTOM, 1, 4, azimuth, elevation, 30, 120);
    getCellContainer()->push_back(cell);
    addDeviceToRadioChannel(cell);

    return cell;
}

Cell*  NetworkManager::createCell (int idCell, gNodeB *targetGNb, int alt, int azimuth)
{
    qDebug() << "NetworkManager: starting to create a cell.";
    Cell *cell = new Cell();
    cell->setTargetGNodeB(targetGNb);
    targetGNb->addCell(cell);
    qDebug() << "new cell.";
    cell->setEquipmentId(idCell);
    cell->setEquipmentType(Equipment::EquipmentType::TYPE_CELL);
    cell->setLinkBudgetParameters();
    
    Mobility *m = new ConstantPosition();
    CartesianCoordinates *position = new CartesianCoordinates(targetGNb->getPosition()->getCoordinates());
    position->setAzimuth(azimuth);
    position->getCoordinates().setAltitude(alt);
    m->setPosition(position);
    cell->setMobilityModel(m);

    cell->setPropagationModel(new PropagationLossModel(PropagationLossModel::PropagationModel::UMA_NLOS));
    qDebug() << "Add antenna array to cell.";

    double azim = cell->getPosition()->getAzimuth();
    double elevation = cell->getPosition()->getAltitude();
    cell->addAntennaArray(AntennaArray::AntennaType::ANTENNA_TYPE_3GPP_CUSTOM, 1, 4, azimuth, elevation, 30, 120);
    getCellContainer()->push_back(cell);
    addDeviceToRadioChannel(cell);

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

gNodeB* NetworkManager::createGNodeB (int id, QGeoCoordinate &coordinates)
{
    debug("Network Manager: Starting to create a gNb. ");
    gNodeB *gNb = new gNodeB(id, coordinates);
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
                                          
    ue->addAntennaArray(AntennaArray::AntennaType::ANTENNA_TYPE_OMNIDIRECTIONAL, 1, 1, 0, posZ, 360, 360);
    ue->setPropagationModel(new PropagationLossModel(PropagationLossModel::PropagationModel::UMA_NLOS));
    getUserEquipmentContainer()->push_back(ue);
    addDeviceToRadioChannel(ue);

    return ue;
}

void NetworkManager::createMultipleUserEquipments(  int number, int lowX, int highX, int lowY, int highY, 
                                                    int borderZ, Cell *cell, gNodeB *targetGNodeB )
{
    for (int i = 1; i <= number; i++) {
        ueIdLocal_ += 1;
        int rndDist = QRandomGenerator::global()->bounded(lowX, highX);
        int rndAzim = QRandomGenerator::global()->bounded(0, 360);
        QGeoCoordinate coordinates = _leftBottom.atDistanceAndAzimuth(rndDist, rndAzim);
        int posZ = 2;
        UserEquipment *ue = new UserEquipment(ueIdLocal_,
                                              coordinates, cell, targetGNodeB,
                                              Mobility::Model::CONSTANT_POSITION);
        ue->addAntennaArray(AntennaArray::AntennaType::ANTENNA_TYPE_OMNIDIRECTIONAL, 1, 1, 0, posZ, 360, 360);
        ue->setPropagationModel(new PropagationLossModel(PropagationLossModel::PropagationModel::UMA_NLOS));
        getUserEquipmentContainer()->push_back(ue);
        addDeviceToRadioChannel(ue);
    }
}

void NetworkManager::attachUEtoCell(Cell *cell, UserEquipment *ue)
{
    qDebug() << "NetworkManager::attachUEtoCell::UE ID-->" << ue->getEquipmentId();
    cell->attachUE(ue);
    //ue->setPhyEntity(cell->getPhyEntity());
    deleteUeFromOtherCells(cell, ue);
}

void NetworkManager::deleteUeFromOtherCells(Cell *targetCell, UserEquipment *targetUe)
{
    for(auto cell: *getCellContainer()) {
        qDebug() << "cell id = " << cell->id_;
        if ( cell != targetCell) {
            int neededIndex = 0;
            int localIdex = 0;
            if(cell->getUserEquipmentContainer()->length() != 0){
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
    while (getCurrentTime() != getWorkingTime())
    {
        qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
        qDebug() << "Current 120 Time Slot ->" << getCurrentTime();
        // Calculate SINR for each Equipment
        calculateSINRPerEquipment(methodSINR_);
        scheduleGNodeB();
        increaseCurrentTime();
    }
}

void NetworkManager::transmitThroughChannel(){
    for ( auto gNb: *getGNodeBContainer() ) {
        fillResourceGridCells(gNb->getCellContainer());
    }
}

void NetworkManager::fillResourceGridCells(QVector<Cell*> *cellContainer)
{
    for (auto cell: *cellContainer) {
        cell->fillResourceGrid();
    }
}

void NetworkManager::receiveFromChannel()
{

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
    qDebug() << "--> ";
    for (auto cell: *cellContainer) {
        qDebug() << "--> ";
        cell->sync120TimeSlot(current120TimeSlot_);
        // TODO: somehow fix the loop
        // TODO: need some fix in order to schedule multiple bandwidth with differens SCS
        int mimoIndex = 0;
        int carrAggIndex = 0;
        int scs = NUMEROLOGY[cell->getPhyEntity()->getAntennaArray()->numerologyIndex_];
        if ( cell->getLocalSystem120TimeSlot() % (int)(120 / scs) == 0 ) {
            qDebug() << cell->getLocalSystem120TimeSlot() % (int)(120 / scs);
            qDebug() << "NetworkManager::scheduleCells:: cell SCS --> " << scs;
            qDebug() << "NetworkManager::scheduleCells:: cell time slot --> " << (int)cell->getLocalSystem120TimeSlot() / (int)(120/scs);
            cell->syncOwnTimeSlot((int) current120TimeSlot_ / (int)(120/scs));
            cell->pathLosDetach();
            initialCellSelection(cell->getLocalOwnTimeSlot());
            generateTrafficPerUE(cell->getUserEquipmentContainer(), (int) current120TimeSlot_ / (int)(120/scs));
            cell->schedule();
        }
    }
}

void NetworkManager::generateTrafficPerUE(QVector<UserEquipment*> *ueContainer, int slot)
{
    for (auto ue: *ueContainer) {
        ue->sync120TimeSlot(current120TimeSlot_);
        ue->generatePacketsPerBearer(slot);
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

void NetworkManager::initialCellSelection(int slot)
{
    double distance;
    double pathLos;
    double rssi;
    double rsrp;

    qDebug() << "NetworkManager::initialAttach()";
    for (auto ue: *getUserEquipmentContainer()) {
        qDebug() << "-->>";
        int localIndex = 0;
        int neededIndex = 0;
        int check = -1;
        double max = -1000;
        int mimoIndex = 0;
        int carrAggIndex = 0;
        if (ue->getSlotToCamp() == slot){
            for (auto cell : *getCellContainer()) {
                qDebug() << "-->>";
                distance = cell->calculateDistanceToUserEquipment(ue);
                pathLos = cell->calculatePathLosToUserEquipment(ue, distance);
                qDebug() << "-->>pathLos";
                rssi = ue->calculateRssiFromCell(cell, pathLos);
                Beam *bim = cell->getPhyEntity()->getAntennaArray()->getBeamContainer().begin()->begin()[0];
                rsrp = ue->calculateRsrpFromRssi(bim->getBandwidthContainer()[0],rssi);
                qDebug() << "-->>rsrp";
                qDebug() << "-->>";
                if ( (rsrp > max) && (rsrp >= -120) ) {
                    max = rsrp;
                    neededIndex = localIndex;
                    check++;
                }
                localIndex++;
                //Debugging
                // qDebug() << "NetworkManager::initialAttach()::UE ID-->" << ue->getEquipmentId();
                qDebug() << "Disnance to cell [" << cell->id_ << "] = " << distance;
                // qDebug() << "NetworkManager::initialAttach()::Path Losses to cell-->" << pathLos;
                // qDebug() << "NetworkManager::initialAttach()::Cell EIRP-->" << cell->getEirp();
                // qDebug() << "NetworkManager::initialAttach()::RSSI-->" << rssi;
                // qDebug() << "NetworkManager::initialAttach()::RSRP-->" << rsrp;
            }
            if(check != -1){
                ue->setTargetCell(getCellContainer()[0][neededIndex]);
                attachUEtoCell(ue->getTargetCell(), ue);
            } else {
                qDebug() << "NetworkManager::initialCellSelection::There are no suitable cell!";
            }
        }
    }
}

double NetworkManager::calculate_sinr_per_user(UserEquipment *user1)
{
    double sinr = 0;
    double interference = 0;
    int mimoIndex = 0;
    int carrAggIndex = 0;
    int count = 0;
    for (auto ue : *getUserEquipmentContainer())
    {
        if (user1 != ue){
            double distance = user1->calculateDistanceToUserEquipment(ue);
            double rssi = user1->calculateRssiFromUserEquipment(ue, distance);
            double rsrp = user1->calculateRsrpFromRssi(user1->getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex], rssi);
            interference = sum_dBm(interference, rsrp);
        }
    }

    return sinr;
}

void NetworkManager::createRadioChannel()
{
    _radioChannel = new RadioChannel();
}

RadioChannel *NetworkManager::getRadioChannel()
{
    return _radioChannel;
}

void NetworkManager::addDeviceToRadioChannel(Equipment *equip)
{
    getRadioChannel()->addDevice(equip);
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
    case NetworkManager::SINRCalcMethod::WO_BUILDINGS:
        calculateSINRPerEquipment_wo_buildings();
        break;
    } 
}

void NetworkManager::calculateSINRPerEquipment_stupid()
{
    double sinr;
    double pathLosses; // in [dBm]

    for ( auto ue : *getUserEquipmentContainer() ) {
        sinr = calculate_sinr_per_user(ue);
    }
}

void NetworkManager::calculateSINRPerEquipment_wo_buildings()
{
    double sinr;
}

void NetworkManager::calculateSINRPerEquipment_signals()
{
    float sinr;
}

void NetworkManager::calculateSINRPerEquipment_signal_doppler()
{
    float sinr;
}


