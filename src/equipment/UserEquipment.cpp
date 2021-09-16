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
    setEquipmentId(id);
    setEquipmentType(Equipment::EquipmentType::TYPE_UE);
    setCurrentCell(cell);
    setTargetGNodeB(targetGNodeB);

    setLinkBudgetParameters();

    // Bearer config
    int bearerId = 3;
    bearerContainer_ = new QVector<RadioBearer *>();
    createDefaultBearer(bearerId);

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

void UserEquipment::setBufferSize(int size)
{
    bufferSize_ = size;
    currentBufferSize_ = size;
}
void UserEquipment::decreaseBuffer(int decSize)
{
    currentBufferSize_ = currentBufferSize_ - decSize;
}
int UserEquipment::getBufferSize()
{
    return currentBufferSize_;
}

void UserEquipment::setHARQ(bool harq)
{
    HARQ_ = harq;
}
bool UserEquipment::getHARQ()
{
    return HARQ_;
}

void UserEquipment::setBSR(bool bsr)
{
    BSR_ = bsr;
}
bool UserEquipment::getBSR()
{
    return BSR_;
}