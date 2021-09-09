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

    // Link Budget Configuration
    setLinkBudgetParameters();

    // Protocols Configuration
    // Physical
    createPhyEntity();
    getPhyEntity()->defaultPhyConfig();

    // MAC Layer
    createMacEntity();
    getMacEntity()->configMacEntity();
    
    // Scheduler
    createScheduler();

    // Bearer config
    int bearerId = 3;
    bearerContainer_ = new QVector<RadioBearer *>();
    createDefaultBearer(bearerId);
}

void Cell::attachUE(UserEquipment *ue)
{
    userEquipmentContainer_->push_back(ue);
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


void Cell::createPhyEntity()
{
    phyEntity_ = new Physical();
}

void Cell::setPhyEntity(Physical *phy)
{
    phyEntity_ = phy;
}

Physical *Cell::getPhyEntity()
{
    return phyEntity_;
}

void Cell::createMacEntity()
{
    macEntity_ = new CellMacEntity();
    macEntity_->setDevice(this);
}

void Cell::setMacEntity(CellMacEntity *cellMac)
{
    macEntity_ = cellMac;
}

CellMacEntity *Cell::getMacEntity()
{
    return macEntity_;
}

void Cell::createScheduler()
{
    scheduler_ = new Scheduler();
}

void Cell::setScheduler(Scheduler *scheduler)
{
    scheduler_ = scheduler;
}

Scheduler *Cell::getScheduler()
{
    return scheduler_;
}
