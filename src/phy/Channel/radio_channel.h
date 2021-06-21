#ifndef RADIO_CHANNEL_H
#define RADIO_CHANNEL_H

#include <QVector>

class Equipment;

class RadioChannel
{
public:
    RadioChannel();

    void addDevice (Equipment* e);
    void delDevice (Equipment* e);
    bool isConnected(Equipment* e);



private:
    QVector<Equipment*> m_connectedDevices;


};

#endif // RADIO_CHANNEL_H
