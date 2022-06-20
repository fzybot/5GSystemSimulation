#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "src/protocols/phy/Symbol.h"
#include "src/protocols/phy/Channel/Bandwidth.h"

#include <QVector>

class Bandwidth;
class RadioChannel;
class MacEntity;
class Symbol;
class TransportBlock;

class Physical
{
protected:
    int                 numerologyIndex_ = 0;
    QVector<Bandwidth*> *bandwidthContainer_;
    double              carrierFreq_;
    Symbol              _symbol;

    float thermalNoise_;

public:
    Physical();

    void defaultPhyConfig();

    void configNewBandwidth(QString fr, QString band, int scs, bool cpType, double ulBw,
                     double dlBw, int ulOffset, int dlOffset, bool tddTrue);
    void addBandwidth(Bandwidth *b);
    QVector<Bandwidth*> *getBandwidthContainer();


    void sendSymbol(QVector<TransportBlock> tbContainer);
};

#endif // PHYSICAL_H
