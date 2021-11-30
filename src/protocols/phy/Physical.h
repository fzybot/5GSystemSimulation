#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "src/protocols/phy/Signal.h"

#include <QVector>

class Bandwidth;
class RadioChannel;
class MacEntity;
class Signal;
class TransportBlock;

class Physical
{
protected:
    int                 numerologyIndex_ = 0;
    RadioChannel        *dlChannel_;
    RadioChannel        *ulChannel_;
    QVector<Bandwidth*> *bandwidthContainer_;
    double              carrierFreq_;
    Signal              txSignal_;

    float thermalNoise_;

public:
    Physical();

    void defaultPhyConfig();

    void setDLChannel(RadioChannel *channel);
    RadioChannel *getDLChannel();

    void setULchannel(RadioChannel *channel);
    RadioChannel *getULChannel();

    void addBandwidth(Bandwidth *b);
    QVector<Bandwidth*> *getBandwidthContainer();
    void configNewBandwidth(QString fr, QString band, int scs, double ulBw,
                     double dlBw, int ulOffset, int dlOffset, bool tddTrue);

    void sendSignal(QVector<TransportBlock> tbContainer);
};

#endif // PHYSICAL_H
