#pragma once

#include "src/protocols/bearers/RadioBearer.h"

#include <QVector>

class RadioBearer;

class Packet
{
protected:
    double  timeStamp_;
    int     size_;
    int     id_;
    int     timeSlotGenerated_;
    int     timeSlotToTransmit_;
    int     timeSlotTransmitted_ = -1000;
    
    RadioBearer *bearer_;

    QVector<bool> data_;

public:
    Packet();
    Packet(QVector<bool> data, double timeStamp, int id);
    Packet(int size, double timeStamp, int id);
    Packet(int size, int slot, int id, RadioBearer *bearer);

    ~Packet();

    void addHeaderSize(int s);
    void setPacketSize(int size);

    void setTimeStamp(double time);
    double getTimeStemp();

    void setId(int pId);
    int getId();

    void setSize(int size); // bytes
    int getSize();

    void setSlotToTransmit(int slot);
    int getSlotToTransmit();

    void setData(QVector<bool> data);
    QVector<bool> getData();

    void setBearer(RadioBearer *bearer);
    RadioBearer *getBearer();

    // TODO: add to raw data realisation according to specifications
    QVector<bool> &toRawData();

    // TODO: add classes for all the headers below
    //    void addRTPHeader(RTPHeader *header);
    //    RTPHeader* getRTPHeader();

    //    void addUDPHeader(UDPHeader *header);
    //    UDPHeader* getUDPHeader();

    //    void addIPHeader(IPHeader *header);
    //    IPHeader* getIPHeader();

    //    void addSDAPHeader (SDAPHeader *header);
    //    SDAPHeader* getSDAPHeader();

    //    void addPDCPHeader(PDCPHeader *header);
    //    PDCDHeader* getPDCPHeader();

    //    void addRLCHeader(RLCHeader *header);
    //    RLCHeader* getRLCHeader();

    //    void addMACHeader(MACHeader *header);
    //    MACHeader* getMACHeader();

    /*
 * Additional headers per each packet from RTP (for VoIP packets) down to
 *
 */
    //    RTPHeader *m_RTPHeader;
    //    UPDHeader *m_UDPHeader;
    //    IPHeader *m_IPHeader;
    //    SDAPHeader *m_SDAPHeader;
    //    PDCPHeader *m_PDCPHeader;
    //    RLCHeader *m_RLCHeader;
    //    MACHeader *m_MACHeader;
};
