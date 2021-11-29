#include "RadioBearer.h"
#include "src/protocols/bearers/QoS/QoSProfile.h"
#include "src/protocols/Packet.h"
#include "src/protocols/bearers/ServiceTrafficProfile.h"

#include <QRandomGenerator>
#include <QDebug>

RadioBearer::RadioBearer()
{
    QoS_ = new QoSProfile();
}

void RadioBearer::createDefaultBearer(int id)
{
    setId(id);
    type_ = RadioBearerType::DRB;
    getQoSProfile()->set5QIValue(8);
}

void RadioBearer::setUserEquipment(UserEquipment *user)
{
    user_ = user;
}

UserEquipment *RadioBearer::getUserEquipment()
{
    return user_;
}

void RadioBearer::createRadioBearer(RadioBearerType type, int id, int QoSProfile)
{
    type_ = type;
    setId(id);
    getQoSProfile()->set5QIValue(QoSProfile);
}

void RadioBearer::setId(int id)
{
    id_ = id;
}

int RadioBearer::getId()
{
    return id_;
}

void RadioBearer::setQoSProfile(QoSProfile *QoS)
{
    QoS_ = QoS;
}

QoSProfile *RadioBearer::getQoSProfile()
{
    return QoS_;
}

void RadioBearer::setTrafficProfile(ServiceTrafficProfile::Profile profile)
{

}

ServiceTrafficProfile &RadioBearer::getTrafficProfile()
{
    return trafficProfile_;
}

void RadioBearer::generatePackets(int number, int currentSlot)
{
    if (this->getQoSProfile() != nullptr) {
        for (int i = 0; i < number; i++) {
            int size = QRandomGenerator::global()->bounded( this->getQoSProfile()->getDataBurstVolumeRange().first, 
                                                            this->getQoSProfile()->getDataBurstVolumeRange().second);
            //qDebug() << "RadioBearer::generatePackets::Packt size ------>>>>> " << size;
            Packet *pack = new Packet(size, currentSlot, i, this);
            pack->setId(gPacketId_);
            gPacketId_++;
            packetsInBuffer_.push_back(pack);
            addToBuffer(size);
        }
    }
}

QVector<Packet*> &RadioBearer::getPacketsContainer()
{
    return packetsInBuffer_;
}

QVector<Packet*> &RadioBearer::getPacketsContainerCurrentSlot(int slot)
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

void RadioBearer::deletePackets(QVector<Packet*> &packetsToDelete)
{
    //getPacketsContainer().removeAll(packetsToDelete);
     if (getPacketsContainer().size() != 0) {
         for (int i = 0; i < packetsToDelete.size(); i++) {
             deletePacket(packetsToDelete[i]);
         }
     } else {
         qDebug() << "RadioBearer::deletePackets::There are no packets to delete";
     }
}

void RadioBearer::deletePacket(Packet *packetToDelete)
{
    for (int i = 0; i < getPacketsContainer().size(); i++){
        if (getPacketsContainer()[i] == packetToDelete){
            qDebug() << "RadioBearer::deletePacket:: packet deleted-->" << getPacketsContainer()[i]->getId();
            decreaseBuffer(packetToDelete->getSize());
            getPacketsContainer().remove(i);
            delete packetToDelete;
            break;
        }
    }
}

void RadioBearer::updatePacketTransmitSlot(int slot)
{
    for(auto packet: getPacketsContainer()){
        packet->setSlotToTransmit(slot);
    }
}

void RadioBearer::showPacketsInBuffer()
{
    for(auto packet: getPacketsContainer()){
        qDebug() << "RadioBearer::showPacketsInBuffer:: Packet" << packet->getId();
    }
}

void RadioBearer::addToBuffer(int size)
{
    bufferSize_ += size;
}

void RadioBearer::decreaseBuffer(int decSize)
{
    bufferSize_ -= decSize;
}

int RadioBearer::getBufferSize()
{
    return bufferSize_;
}

int &RadioBearer::getCounterDataTransmitted()
{
    return counterDataTransmitted_;
}
int &RadioBearer::getCounterSlotTransmitted()
{
    return counterSlotTransmitted_;
}
