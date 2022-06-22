#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "src/protocols/phy/Symbol.h"
#include "src/protocols/phy/Bandwidth.h"

#include <QVector>

class Bandwidth;
class RadioChannel;
class MacEntity;
class Symbol;
class TransportBlock;

class Physical
{
public:
    enum class MIMO_MODE
    {
      SISO_1x1,
      MIMO_2x2,
      MIMO_4x4
    };

public:
    int                 numerologyIndex_ = 0;
    QVector<Bandwidth*> *bandwidthContainer_;
    QVector<Bandwidth*> *bandwidthContainerCarrierAgg_;
    double              carrierFreq_;
    Physical::MIMO_MODE _mimoMode;

    float thermalNoise_;

public:
    Physical();

    void defaultPhyConfig(Physical::MIMO_MODE _mimoMode);

    void configNewBandwidth(QString fr, QString band, int scs, bool cpType, double ulBw,
                            double dlBw, int ulOffset, int dlOffset, bool tddTrue);
    void addBandwidth(Bandwidth *b);
    QVector<Bandwidth*> *getBandwidthContainer();

    Physical::MIMO_MODE &getMimoMode();

    void sendSymbol(QVector<TransportBlock> tbContainer);
};

#endif // PHYSICAL_H
