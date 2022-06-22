#include "Physical.h"
#include "src/protocols/phy/Bandwidth.h"
#include "src/protocols/phy/Symbol.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/commonParameters.h"

Physical::Physical()
{
    bandwidthContainer_ = new QVector<Bandwidth*>;
}

void Physical::defaultPhyConfig(Physical::MIMO_MODE mode)
{
    _mimoMode = mode;
    switch ( _mimoMode )
      {
         case Physical::MIMO_MODE::MIMO_2x2:
            configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true);
            configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true);
            break;
         case Physical::MIMO_MODE::MIMO_4x4:
            configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true);
            configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true);
            configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true);
            configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true);
            break;
         default:
            configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true);
      }
}

void Physical::addBandwidth(Bandwidth *b)
{
    bandwidthContainer_->push_back(b);
}

QVector<Bandwidth*> *Physical::getBandwidthContainer()
{
    return bandwidthContainer_;
}

void Physical::configNewBandwidth( QString fr, QString band, int scs, bool cpType, double ulBw,
                                double dlBw, int ulOffset, int dlOffset, bool tddTrue)
{
    //QString fr, QString band, int scs, double ulBw, double dlBw, int ulOffset, int dlOffset, bool tddTrue = true
    Bandwidth *bw = new Bandwidth(fr, band, scs, cpType, ulBw, dlBw, ulOffset, dlOffset, tddTrue);
    bw->setCoresetSize(2, bw->getNumberOfPRB() - 30);
    addBandwidth(bw);
}

Physical::MIMO_MODE &Physical::getMimoMode()
{
    return _mimoMode;
}
