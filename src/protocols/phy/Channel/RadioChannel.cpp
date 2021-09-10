#include "RadioChannel.h"
#include "src/debug.h"

#include "src/equipment/Equipment.h"
#include "src/protocols/phy/propagationModels.h"

#include <QDebug>

RadioChannel::RadioChannel()
{
     debug("Radio channel is created: ");
     connectedDevices_ = new QVector<Equipment*>;
     //propagationLossModel_ = new PropagationLossModel();
}

RadioChannel::~RadioChannel()
{
    connectedDevices_->clear();
    delete connectedDevices_;
    delete propagationLossModel_;
}

void RadioChannel::setChannelId(int id)
{
    channelId_ = id;
}

int RadioChannel::getChannelId()
{
    return channelId_;
}

void RadioChannel::addDevice(Equipment *e)
{
    debug("RadioChannel: adding an Equipment ");
    // TODO: check the existance of the Equipment* e
    if (isConnected(e) == false) {
        getConnectedDevices()->push_back(e);
        e->print();
        debug("RadioChannel: equipment is successfully added");
    }
    else{
        qDebug() << "RadioChannel: equipment is already connected to the channel";
    }
}

QVector<Equipment*>* RadioChannel::getConnectedDevices()
{
    return connectedDevices_;
}

void RadioChannel::delDevice(Equipment *e)
{
    debug("RadioChannel: Deleting device with ID: ", e->getEquipmentId());
    QVector<Equipment*> *newList = new QVector<Equipment*>();
    for (auto equip : *getConnectedDevices())
    {
        if (equip->getEquipmentId() != e->getEquipmentId()) {
            newList->push_back(equip);
        }
    }
    connectedDevices_->clear();
    delete connectedDevices_;
    connectedDevices_ = newList;
    debug("RadioChannel: Successfully deleted");
}

bool RadioChannel::isConnected(Equipment *e)
{
    for (auto equip : *getConnectedDevices()) {
        if (equip->getEquipmentId() == e->getEquipmentId()) {
            return true;
        }
    }
    return false;
}

void RadioChannel::printConnectedDevices()
{
    qDebug() << "Radio Channel: List of connected devices: ";
    for (auto equip : *getConnectedDevices()) {
        qDebug() << "ID: " << equip->getEquipmentId();
    }
}
