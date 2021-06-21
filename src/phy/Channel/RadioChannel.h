#pragma once


#include "src/equipment/Equipment.h"

#include <QVector>


class RadioChannel
{
private:
    QVector<Equipment*> m_connectedDevices;

public:
    RadioChannel();

    void addDevice(Equipment* e);
    void delDevice(Equipment* e);
    bool isConnected(Equipment* e);
};
