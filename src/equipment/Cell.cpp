#include "Cell.h"
#include "src/equipment/UserEquipment.h"
#include "src/protocols/mac_layer/CellMacEntity.h"
#include "src/equipment/gNodeB.h"

Cell::Cell()
{
    userEquipmentContainer_ = new QVector<UserEquipment*>();

    setLinkBudgetParameters();
    createMacEntity();
    getMacEntity()->configMacEntity();
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

void Cell::createMacEntity()
{
    macEntity_ = new CellMacEntity();
}

CellMacEntity *Cell::getMacEntity()
{
    return macEntity_;
}



