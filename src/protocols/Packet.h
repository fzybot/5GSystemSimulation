#pragma once

#include "src/protocols/bearers/RadioBearer.h"

#include <QVector>

class RadioBearer;

class Packet
{
protected:
    double  timeStamp_;
    int     headerSize_ = 20; // [bytes]
    int     size_ = 0; // [bytes]
    int     id_;
    int     timeSlotGenerated_;
    int     timeSlotToTransmit_;
    int     timeSlotTransmitted_ = -1000;

    bool _isParent = true;

    Packet *_parent = nullptr;
    QVector<Packet *> _childs;

    RadioBearer *bearer_;

    QVector<bool> data_;

public:
    Packet();
    Packet(int size, double timeStamp, int id);
    Packet(int size, int slot, int id, RadioBearer *bearer);
    Packet(QVector<bool> &data, Packet *parent, QVector<Packet *> &buffer);

    ~Packet();

    bool isParent();
    Packet *getParent();

    void setHeaderSize(int s);
    int getHeaderSize();
    void addHeaderSize(int s);
    void setPacketSize(int size);

    void setTimeStamp(double time);
    double getTimeStamp();

    void setId(int pId);
    int getId();

    void setSize(int size); // bytes
    int getSize();
    int getSizeBits();

    void setSlotGenerated(int slot);
    int getSlotGenerated();

    void setSlotToTransmit(int slot);
    int getSlotToTransmit();

    void setSlotTransmitted(int transmittedSlot);
    int getSlotTransmitted();

    void generateRandomData();
    void copyData(QVector<bool> &data);
    QVector<bool> &getData();

    void setBearer(RadioBearer *bearer);
    RadioBearer *getBearer();

    // TODO: add to raw data realisation according to specifications
    QVector<bool> &toRawData();

private:
    void setParent(Packet *parent);

};
