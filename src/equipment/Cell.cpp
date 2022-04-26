#include "Cell.h"
#include "src/equipment/UserEquipment.h"
#include "src/protocols/mac_layer/CellMacEntity.h"
#include "src/equipment/gNodeB.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"


Cell::Cell()
{
    userEquipmentContainer_ = new QVector<UserEquipment*>();

    // Protocols Configuration
    // Physical
    createPhyEntity();
    getPhyEntity()->defaultPhyConfig();

    // MAC Layer
    createMacEntity();
    getMacEntity()->configMacEntity();
    
    // Scheduler
//    createScheduler(Scheduler::SchedulingAlgorithm::ROUND_ROBIN);
//    scheduler_->setCell(this);
}

bool Cell::chechUeExistance(UserEquipment *ue)
{
    for(auto user: *getUserEquipmentContainer()) {
        if (ue == user){
            return true;
        }
    }
    return false;
}

void Cell::attachUE(UserEquipment *ue)
{
    if(!chechUeExistance(ue)){
        userEquipmentContainer_->push_back(ue);
    }
}

QVector<UserEquipment*> *Cell::getUserEquipmentContainer (void)
{
    return userEquipmentContainer_;
}

void Cell::setTargetGNodeB(gNodeB *gNb)
{
    targetGNodeB_ = gNb;
}

gNodeB *Cell::getTargetGNodeB()
{
    return targetGNodeB_;
}

void Cell::setAntenna(Antenna *ant)
{
    antenna_ = ant;
}
Antenna *Cell::getAntenna()
{
    return antenna_;
}

void Cell::createMacEntity()
{
    macEntity_ = new CellMacEntity(this);
    macEntity_->createScheduler(Scheduler::SchedulingAlgorithm::ROUND_ROBIN);
}

void Cell::setMacEntity(CellMacEntity *cellMac)
{
    macEntity_ = cellMac;
}

CellMacEntity *Cell::getMacEntity()
{
    return macEntity_;
}

void Cell::schedule()
{
    getMacEntity()->schedule();
}

void Cell::pathLosDetach()
{
    double distance;
    double pathLos;
    double rssi;
    double rsrp;

    int localIndex = 0;
    for (auto ue : *getUserEquipmentContainer())
    {
        distance = ue->calculateDistanceToCell(this);
        pathLos = ue->calculatePathLosToCell(this, distance);
        rssi = ue->calculateRssiFromCell(this, pathLos);
        rsrp = ue->calculateRsrpFromRssi(this->getPhyEntity()->getBandwidthContainer()[0][0], rssi);
        if (rsrp < -120){
            detachUeFromCell(localIndex, 1); // Reason 1 - due to path loss
            ue->setSlotToCamp(getLocalOwnTimeSlot() + 30); // 100 time for cell reselection/handover)
        }
        localIndex++;
    }
}

void Cell::detachUeFromCell(int localIndex, int reason)
{
    getUserEquipmentContainer()->remove(localIndex);

    switch (reason)
    {
    case 1:
        qDebug() << "NetworkManager::detachUeFromCell()::detached due to 'Path Los'";
        break;
    case 2:
        qDebug() << "NetworkManager::detachUeFromCell()::detached due to 'HandOver'";
        break;
    default:
        break;
    }
}
