#include "Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/phy/Symbol.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/commonParameters.h"

Physical::Physical()
{
    bandwidthContainer_ = new QVector<Bandwidth*>;
}

void Physical::defaultPhyConfig()
{
    configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], 10, 50, 0, 0, true);
}

void Physical::addBandwidth(Bandwidth *b)
{
    bandwidthContainer_->push_back(b);
}

QVector<Bandwidth*> *Physical::getBandwidthContainer()
{
    return bandwidthContainer_;
}

void Physical::configNewBandwidth( QString fr, QString band, int scs, double ulBw,
                                double dlBw, int ulOffset, int dlOffset, bool tddTrue)
{
    //QString fr, QString band, int scs, double ulBw, double dlBw, int ulOffset, int dlOffset, bool tddTrue = true
    Bandwidth *bw = new Bandwidth(fr, band, scs, ulBw, dlBw, ulOffset, dlOffset, tddTrue);
    bw->setCoresetSize(2, bw->getNumberOfPRB() - 30);
    addBandwidth(bw);
}

void Physical::sendSymbol(QVector<TransportBlock> tbContainer)
{
    //txSignal_.fromTbToSignal();
}
