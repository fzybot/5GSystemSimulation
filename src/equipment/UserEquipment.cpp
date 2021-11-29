#include "UserEquipment.h"
#include "src/core/CartesianCoordinates.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/equipment/mobility/ConstantPosition.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Physical.h"

#include <QRandomGenerator>


// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

UserEquipment::UserEquipment()
{
    targetGNodeB_ = nullptr;
    targetCell_ = nullptr;
}

UserEquipment::UserEquipment(int id, 
                             double posX, double posY, double posZ, 
                             Cell *cell, gNodeB *targetGNodeB, 
                             Mobility::Model model)
{
    setEquipmentId(id);
    setEquipmentType(Equipment::EquipmentType::TYPE_UE);
    setTargetCell(cell);
    setTargetGNodeB(targetGNodeB);

    // Physical
    setLinkBudgetParameters();

    // Bearer config
    // Default Bearer
    int bearerId = 3;
    bearerContainer_ = new QVector<RadioBearer *>();
    createDefaultBearer(bearerId);

    // Additional Data Bearer
    bearerId++;
    int randQoSProfile = QRandomGenerator::global()->bounded(1, 9);
    createBearer(RadioBearer::RadioBearerType::DRB, bearerId, randQoSProfile);

    // Random SINR
    int localSINR = QRandomGenerator::global()->bounded(0, 19);
    setSINR(localSINR);

    // Generate Traffic per each bearer
    //generatePacketsPerBearer();

    // Positioning
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

void UserEquipment::setTargetCell(Cell *cell)
{
    targetCell_ = cell;
}

Cell *UserEquipment::getTargetCell()
{
    return targetCell_;
}

void UserEquipment::setTargetGNodeB(gNodeB *gNb)
{
    targetGNodeB_ = gNb;
}

gNodeB *UserEquipment::getTargetGNodeB()
{
    return targetGNodeB_;
}

void UserEquipment::setSlotToCamp(int slot)
{
    slotToCampOnCell_ = slot;
}

int UserEquipment::getSlotToCamp()
{
    return slotToCampOnCell_;
}

void UserEquipment::setBSR(bool bsr)
{
    BSR_ = bsr;
}

bool UserEquipment::getBSR()
{
    return BSR_;
}

void UserEquipment::setMeasurementGap(bool gap)
{
    measurementGAP_ = gap;
}

bool UserEquipment::getMeasurementGap()
{
    return measurementGAP_;
}

void UserEquipment::setDRX(bool drx)
{
    DRX_ = drx;
}

bool UserEquipment::getDRX()
{
    return DRX_;
}

void UserEquipment::setSINR(double sinr)
{
    sinr_ = sinr;
}

double UserEquipment::getSINR()
{
    return sinr_;
}

void UserEquipment::generatePacketsPerBearer(int slot)
{
    for(auto bearer: *getBearerContainer()) {
        bearer->generatePackets(2, slot);
    }
}

int UserEquipment::getBufferSize()
{
    int size = 0;
    for(auto bearer : *getBearerContainer()){
        size += bearer->getBufferSize();
    }
    return size;
}
