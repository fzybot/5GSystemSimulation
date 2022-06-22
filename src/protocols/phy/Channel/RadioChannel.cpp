#include "RadioChannel.h"
#include "src/debug.h"

#include "src/equipment/Equipment.h"
#include "src/protocols/phy/Channel/propagationModels.h"

#include <QDebug>
#include <QRandomGenerator>

RadioChannel::RadioChannel()
{
     debug("Radio channel is created: ");
     connectedDevices_ = new QVector<Equipment*>;
     //propagationLossModel_ = new PropagationLossModel();
}

RadioChannel::RadioChannel(RadioChannel::ChannelModel channel_model, int noise, PropagationLossModel *model)
{
    setNoiseVal(noise);
    switch (channel_model)
    {
        case RadioChannel::ChannelModel::AWGN_CHANNEL:
            setPathNumber(1);
            addPath(0, 0, 0);
            break;
        case RadioChannel::ChannelModel::RAYLEIGH_CHANNEL:
            setPathNumber(6);
            break;
        case RadioChannel::ChannelModel::RICE_CHANNEL:
            setPathNumber(5);
            break;
        case RadioChannel::ChannelModel::EPA_5HZ:
            setPathNumber(7);
            addPath(0, 0, 0);
            addPath(1, 30, 1.0);
            addPath(2, 70, 2.0);
            addPath(3, 90, 3.0);
            addPath(4, 110, 8.0);
            addPath(5, 190, 17.2);
            addPath(6, 410, 20.8);
            break;
        case RadioChannel::ChannelModel::EVA_70HZ:
            setPathNumber(9);
            addPath(0, 0, 0);
            addPath(1, 30, 1.5);
            addPath(2, 150, 1.4);
            addPath(3, 310, 13.6);
            addPath(4, 370, 0.6);
            addPath(5, 710, 9.1);
            addPath(6, 1090, 7.0);
            addPath(7, 1730, 12.0);
            addPath(8, 2510, 16.9);
            break;
        case RadioChannel::ChannelModel::ETU_300HZ:
            setPathNumber(9);
            addPath(0, 0, 1.0);
            addPath(1, 50, 1.0);
            addPath(2, 120, 1.0);
            addPath(3, 200, 0.0);
            addPath(4, 230, 0.0);
            addPath(5, 500, 0.0);
            addPath(6, 1600, 3.0);
            addPath(7, 2300, 5.0);
            addPath(8, 5000, 7.0);
            break;
        case RadioChannel::ChannelModel::AWGN_DOPPLER_CHANNEL:
            setPathNumber(1);
            addPath(0, 0, 0);
            break;
        case RadioChannel::ChannelModel::RAYLEIGH_DOPPLER_CHANNEL:
            setPathNumber(6);
            break;
        case RadioChannel::ChannelModel::RICE_DOPPLER_CHANNEL:
            setPathNumber(5);
            break;
        case RadioChannel::ChannelModel::DOPPLER_CHANNEL:
            setPathNumber(1);
            addPath(0, 0, 0);
            break;
    }
}

RadioChannel::~RadioChannel()
{
    connectedDevices_->clear();
    delete connectedDevices_;
    delete propagationLossModel_;
}

void RadioChannel::setNoiseVal(int noise)
{
    _noiseValue = noise;
}

void RadioChannel::setPathNumber(int nPath)
{
    _nPath = nPath;
    _pathCharacteristics.resize(nPath);
}

int RadioChannel::getPathNumber()
{
    return _nPath;
}

void RadioChannel::addPath(int pathIndex, float delay, float pathLoss)
{
    _pathCharacteristics[pathIndex].resize(2);
    _pathCharacteristics[pathIndex][0] = delay;
    _pathCharacteristics[pathIndex][1] = pathLoss;
}

void RadioChannel::generateRandomPaths(int number, int maxDistance)
{
    // int rnd;
    // int border = floor(borderHigh / getPathNumber());
    // int low = borderLow;
    // int high = border;
    // for (int i = 0; i < getPathNumber(); i++)
    // {
    //     rnd = QRandomGenerator::global()->bounded(low, high);
    //     low = low + border + 1;
    //     high = high + border;
    //     addPath(i, rnd, 0);
    // }
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
