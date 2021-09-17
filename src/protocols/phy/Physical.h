#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <QVector>
class Bandwidth;
class RadioChannel;
class MacEntity;
class Signal;

class Physical
{
protected:
    RadioChannel *dlChannel_;
    RadioChannel *ulChannel_;
    QVector<Bandwidth*> *bandwidthContainer_;
    double carrierFreq_;

    Signal *txSignal_;

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
    void configBandwidth();
};

#endif // PHYSICAL_H
