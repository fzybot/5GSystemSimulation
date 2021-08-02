#include "UserEquipment.h"
#include "src/core/CartesianCoordinates.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/equipment/mobility/ConstantPosition.h"


// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

UserEquipment::UserEquipment()
{

}

UserEquipment::UserEquipment(int id, 
                             double posX, double posY, double posZ, 
                             Cell *cell, gNodeB *targetGNodeB, 
                             Mobility::MobilityModel model)
{
    setEquipmentID(id);
    setEquipmentType(Equipment::TYPE_UE);
    setCurrentCell(cell);
    setTargetGNodeB(targetGNodeB);

    Mobility *m;
    if (model == Mobility::CONSTANT_POSITION)
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

void UserEquipment::setTargetGNodeB(gNodeB *gNb)
{
    targetGNodeB_ = gNb;
}