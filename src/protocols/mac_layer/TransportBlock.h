#pragma once

#include "src/protocols/Packet.h"

#include <QVector>

class UserEquipment;

class TransportBlock
{

private:

    UserEquipment   *user_;

    Packet              packet_;
    int                 size_ = 0; // TODO: check actual overhead value calculation based on packets and their size
    int                 sizeCodeRate_ = 0;
    QVector<bool>       tbsData_;
    QVector<Packet*>    packetContainer_;
    QVector<int>        prbIndexes_;
    int                 nPrb_ = 0;
    int                 slotToTransmit_ = 0;
    int                 slotInitialized_ = 0;
    int                 slotTransmitted_;
    int                 mOrder_;

    bool HARQ_ = false;

public:
    TransportBlock();
    TransportBlock(Packet &packet);

    void setUserEquipment(UserEquipment *user);
    UserEquipment *getUserEquipment();

    void setPacket(Packet &packet);
    Packet &getPacket();

    void appendPacket(Packet *packet, int size);
    QVector<Packet*> &getPacketContainer();

    void setSize(int size);
    void addSize(int size);
    int getSize();

    void setSizeWoCodeRate(int size);
    void addSizeWoCodeRate(int size);
    int getSizeWoCodeRate();

    void setNumberOfPrb(int number);
    int getNumberOfPrb();

    void setSlotToTransmit(int slot);
    int getSlotToTransmit();

    void setSlotInitialized(int slot);
    int getSlotInitialized();

    void setSlotTransmitted(int slot);
    int getSlotTransmitted();

    void setHarqStatus(bool status);
    bool getHarqStatus();

    void setModulationOrder(int order);
    int getModulationOrder();

    void clear();
};
