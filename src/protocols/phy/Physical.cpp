#include "Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/phy/Signal.h"
#include "src/protocols/phy/Channel/RadioChannel.h"

Physical::Physical()
{
    carrierFreq_ = 1800;
    bandwidthContainer_ = new QVector<Bandwidth*>;
    txSignal_ = new Signal();
    dlChannel_ = new RadioChannel();
    ulChannel_ = new RadioChannel();
    generateBandwidth();
}

void Physical::setDLChannel(RadioChannel *channel)
{

}
RadioChannel *Physical::getDLChannel()
{
    
}

void Physical::addBandwidth(Bandwidth *b)
{
    bandwidthContainer_->push_back(b);
}

QVector<Bandwidth*> *Physical::getBandwidthContainer()
{
    return bandwidthContainer_;
}

void Physical::generateBandwidth()
{
    //QString fr, QString band, int scs, double ulBw, double dlBw, int ulOffset, int dlOffset, bool tddTrue = true
    Bandwidth *bw = new Bandwidth("FR1", "n3", 15, 10, 20, 0, 0, true);
    bandwidthContainer_->push_back(bw);
    
}