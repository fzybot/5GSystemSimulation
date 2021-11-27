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
    createPhyEntity();
    getPhyEntity()->defaultPhyConfig();

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

void UserEquipment::addToBuffer(int size)
{
    bufferSize_ += size;
}

void UserEquipment::decreaseBuffer(int decSize)
{
    bufferSize_ -= decSize;
}

int UserEquipment::getBufferSize()
{
    return bufferSize_;
}

void UserEquipment::generatePacketsPerBearer(int slot)
{
    for(auto bearer: *getBearerContainer()) {
        this->generatePackets(2, slot, bearer);
    }
}


void UserEquipment::generatePackets(int number, int currentSlot, RadioBearer *bearer)
{
    if (bearer->getQoSProfile() != nullptr) {
        for (int i = 0; i < number; i++) {
            int size = QRandomGenerator::global()->bounded( bearer->getQoSProfile()->getDataBurstVolumeRange().first, 
                                                            bearer->getQoSProfile()->getDataBurstVolumeRange().second);
            //qDebug() << "UserEquipment::generatePackets::Packt size ------>>>>> " << size;
            Packet  *pack = new Packet(size, currentSlot, i, bearer);
            pack->setId(gPacketId_);
            gPacketId_++;
            packetsInBuffer_.push_back(pack);
            addToBuffer(size);
        }
    }
}

QVector<Packet*> &UserEquipment::getPacketsContainer()
{
    return packetsInBuffer_;
}

QVector<Packet*> &UserEquipment::getPacketsContainerCurrentSlot(int slot)
{
    packetsCurrentSlot_.clear();
    for (auto packet : getPacketsContainer())
    {
        if(packet->getSlotToTransmit() == slot){
            packetsCurrentSlot_.append(packet);
        }
    }
    return packetsCurrentSlot_;
}

void UserEquipment::deletePackets(QVector<Packet*> &packetsToDelete)
{
    //getPacketsContainer().removeAll(packetsToDelete);
     if (getPacketsContainer().size() != 0) {
         for (int i = 0; i < packetsToDelete.size(); i++) {
             deletePacket(packetsToDelete[i]);
         }
     } else {
         qDebug() << "UserEquipment::deletePackets::There are no packets to delete";
     }
}

void UserEquipment::deletePacket(Packet *packetToDelete)
{
    for (int i = 0; i < getPacketsContainer().size(); i++){
        if (getPacketsContainer()[i] == packetToDelete){
            qDebug() << "UserEquipment::deletePacket:: packet deleted-->" << getPacketsContainer()[i]->getId();
            decreaseBuffer(packetToDelete->getSize());
            getPacketsContainer().remove(i);
            delete packetToDelete;
            break;
        }
    }
}

void UserEquipment::updatePacketTransmitSlot(int slot)
{
    for(auto packet: getPacketsContainer()){
        packet->setSlotToTransmit(slot);
    }
}

void UserEquipment::showPacketsInBuffer()
{
    for(auto packet: getPacketsContainer()){
        qDebug() << "UserEquipment::showPacketsInBuffer:: Packet" << packet->getId();
    }
}
