#ifndef PHYSICAL_H
#define PHYSICAL_H

class Bandwidth;
class RadioChannel;
class MacEntity;
class Signal;

class Physical
{
protected:
    RadioChannel *dlChannel_;
    RadioChannel *ulChannel_;
    Bandwidth *bandwidth_;
    double carrierFreq_;

    Signal *txSignal_;

    float thermalNoise_;

public:
    Physical();

    void setDLChannel(RadioChannel *channel);
    RadioChannel *getDLChannel();

    void setULchannel(RadioChannel *channel);
    RadioChannel *getULChannel();
};

#endif // PHYSICAL_H
