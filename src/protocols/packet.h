#ifndef PACKET_H
#define PACKET_H

#include <QVector>

class Packet
{
public:
    Packet() = default;
    Packet(QVector<bool> data, double timeStamp, int id);
    virtual ~Packet();

    void setTimeStamp(double time);
    double getTimeStemp();
    void setId(int pId);
    int getId();

    void setData(QVector<bool> data);
    QVector<bool> getData();


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

private:
    void addHeaderSize(int s);
    void setPacketSize(int size);


private:

    double m_timeStamp;
    int m_size;
    int m_id;

    QVector<bool> m_data;

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

#endif // PACKET_H
