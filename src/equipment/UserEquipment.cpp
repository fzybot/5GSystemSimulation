#include "UserEquipment.h"
#include "src/core/CartesianCoordinates.h"
#include "src/equipment/mobility/Mobility.h"
#include "src/equipment/mobility/ConstantPosition.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"

#include <QRandomGenerator>


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
    // Default Bearer
    int bearerId = 3;
    bearerContainer_ = new QVector<RadioBearer *>();
    createDefaultBearer(bearerId);

    // Additional Data Bearer
    bearerId++;
    int randQoSProfile = QRandomGenerator::global()->bounded(1, 9);
    createBearer(RadioBearer::RadioBearerType::DRB, bearerId, randQoSProfile);

    // Random SINR
    int localSINR = QRandomGenerator::global()->bounded(-7, 25);
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

void UserEquipment::generatePacketsPerBearer()
{
    for(auto bearer: *getBearerContainer()) {
        this->generatePackets(100, localSystem120TimeSlot_, bearer);
    }
}


void UserEquipment::generatePackets(int number, int currentSlot, RadioBearer *bearer)
{
    if (bearer->getQoSProfile() != nullptr) {
        for (int i = 0; i < number; i++) {
            int size = QRandomGenerator::global()->bounded( bearer->getQoSProfile()->getDataBurstVolumeRange().first, 
                                                            bearer->getQoSProfile()->getDataBurstVolumeRange().second);
            qDebug() << "UserEquipment::generatePackets::Packt size ------>>>>> " << size;
            Packet  *pack = new Packet(size, currentSlot, i, bearer);
            packetsInBuffer_.push_back(pack);
        }
    }
}

QVector<Packet*> &UserEquipment::getPacketsContainer()
{
    return packetsInBuffer_;
}
