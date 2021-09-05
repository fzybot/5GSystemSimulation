#include "UserEquipment.h"
#include "src/core/CartesianCoordinates.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/equipment/mobility/ConstantPosition.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"


// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

UserEquipment::UserEquipment()
{
    targetGNodeB_ = nullptr;
    currentCell_ = nullptr;
}

UserEquipment::UserEquipment(int id, 
                             double posX, double posY, double posZ, 
                             Cell *cell, gNodeB *targetGNodeB, 
                             Mobility::Model model)
{
    setEquipmentID(id);
    setEquipmentType(Equipment::TYPE_UE);
    setCurrentCell(cell);
    setTargetGNodeB(targetGNodeB);

    setLinkBudgetParameters();

    Mobility *m;
    if (model == Mobility::Model::CONSTANT_POSITION)
    {
        m = new ConstantPosition ();
    }
    else
    {
        qDebug() << "ERROR: incorrect Mobility Model"<< endl;
        exit(1);
    }
    CartesianCoordinates *position = new CartesianCoordinates(posX, posY, posZ);
    m->setPosition(position);
    setMobilityModel(m);
    delete position;
}

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void UserEquipment::setCurrentCell(Cell *cell)
{
    currentCell_ = cell;
}

Cell *UserEquipment::getCurrentCell()
{
    return currentCell_;
}

void UserEquipment::setTargetGNodeB(gNodeB *gNb)
{
    targetGNodeB_ = gNb;
}

gNodeB *UserEquipment::getTargetGNodeB()
{
    return targetGNodeB_;
}
