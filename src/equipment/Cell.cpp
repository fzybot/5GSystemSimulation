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

void Cell::createMacEntity()
{
    macEntity_ = new CellMacEntity();
}

CellMacEntity *Cell::getMacEntity()
{
    return macEntity_;
}

