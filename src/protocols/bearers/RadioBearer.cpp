#include "RadioBearer.h"
#include "src/protocols/QoS/QoSProfile.h"
#include "src/protocols/Packet.h"
#include "src/protocols/TrafficProfile.h"

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

void RadioBearer::setTrafficProfile(TrafficProfile::Profile profile)
{

}

TrafficProfile &RadioBearer::getTrafficProfile()
{
    return trafficProfile_;
}

void RadioBearer::generatePackets(int number, int currentSlot)
{
    if (QoS_ != nullptr) {
        for (int i = 0; i < number; i++) {
            int size = QRandomGenerator::global()->bounded( getQoSProfile()->getDataBurstVolumeRange().first, 
                                                            getQoSProfile()->getDataBurstVolumeRange().second);
            qDebug() << "Packt size ------>>>>> " << size;
            Packet pack(size, currentSlot, i);
            packetsInBuffer_.push_back(pack);
        }
    }
}

QVector<Packet> &RadioBearer::getPacketsContainer()
{
    return packetsInBuffer_;
}

int &RadioBearer::getCounterDataTransmitted()
{
    return counterDataTransmitted_;
}
int &RadioBearer::getCounterSlotTransmitted()
{
    return counterSlotTransmitted_;
}
