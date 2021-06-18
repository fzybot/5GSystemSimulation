#ifndef RADIOCHANNEL_H
#define RADIOCHANNEL_H

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

#endif // RADIOCHANNEL_H
