#include "Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/phy/Signal.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/commonParameters.h"

Physical::Physical()
{
    bandwidthContainer_ = new QVector<Bandwidth*>;
    txSignal_ = new Signal();
    dlChannel_ = new RadioChannel();
    ulChannel_ = new RadioChannel();
}

void Physical::defaultPhyConfig()
{
    configBandwidth();
}

void Physical::setDLChannel(RadioChannel *channel)
{
    dlChannel_ = channel;
}
RadioChannel *Physical::getDLChannel()
{
    return dlChannel_;
}

void Physical::addBandwidth(Bandwidth *b)
{
    bandwidthContainer_->push_back(b);
}

QVector<Bandwidth*> *Physical::getBandwidthContainer()
{
    return bandwidthContainer_;
}

void Physical::configBandwidth()
{
    //QString fr, QString band, int scs, double ulBw, double dlBw, int ulOffset, int dlOffset, bool tddTrue = true
    Bandwidth *bw = new Bandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], 10, 20, 0, 0, true);
    addBandwidth(bw);
    
}
