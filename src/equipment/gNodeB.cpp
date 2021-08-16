#include "gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/equipment/mobility/ConstantPosition.h"
#include "src/core/CartesianCoordinates.h"

#include "src/debug.h"

// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

gNodeB::gNodeB()
{
    
    //dataSize = ((bandwidth * 1000) / SCS) * 2 * 14 * mimoLayers;
}

gNodeB::gNodeB(int id, Cell *cell, double posX, double posY, double posZ)
{
    debug("gNodeB: Starting to create a gNb");
    setEquipmentID(id);
    setEquipmentType(Equipment::TYPE_GNODEB);
    addCell(cell);

    CartesianCoordinates *position = new CartesianCoordinates(posX, posY, posZ);
    Mobility *m = new ConstantPosition();
    m->setPosition(position);
    setMobilityModel(m);
    // Becouse in Mobility class a new object is created
    delete position;
}

// ----- [ GETTERS\SETTERS ] -------------------------------------------------------------------------------------------\

QVector<UserEquipment*> *gNodeB::getUserEquipmentContainer (void)
{
    return userEquipmentContainer_;
}

QVector<Cell*>* gNodeB::getCellContainer (void)
{
    debug("gNodeB: getting cell container");
    return cellContainer_;
}

void gNodeB::addCell(Cell *cell)
{
    debug("gNodeB: adding cell");
    cell_ = cell;
    //getCellContainer()->push_back(cell);
    debug("gNodeB: cell container", cell_->getEquipmentID());
}

Cell *gNodeB::getCellByID(int id)
{
    for (auto cell : *getCellContainer()) {
        if (cell->getEquipmentID() == id) {
            return cell;
        }
    }
    return nullptr;
}
