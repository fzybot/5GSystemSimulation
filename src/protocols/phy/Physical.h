#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "src/protocols/phy/Symbol.h"
#include "src/protocols/phy/Bandwidth.h"
#include "src/equipment/antenna/AntennaArray.h"
#include "src/protocols/phy/PhyConfigs.h"


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

private:
    Physical::MIMO_MODE _mimoMode;
    AntennaArray *_antennaArray;
    conf_band bandConfig;

    int _nominalPower = 1;
    int numerologyIndex_ = 0;
    double  carrierFreq_;
    float thermalNoise_;
    
    // per mimo and CarrierAgg
    QVector< QVector<Bandwidth*> >      _bandwidthContainerMimoCarrierAgg;

public:
    Physical(); 

    void defaultPhyConfig(Physical::MIMO_MODE _mimoMode, int carrierAgg);
    void configNewBandwidth(QString fr, QString band, int scs, bool cpType, double ulBw,
                            double dlBw, int ulOffset, int dlOffset, bool tddTrue, int mimoIndex, int carrAggIndex);
    void addBandwidth(int carrierAggIndex, Bandwidth *b);

    QVector< QVector<Bandwidth*> > &getBandwidthContainer();
    Physical::MIMO_MODE &getMimoMode();

    void addAntennaArray(AntennaArray::AntennaType type, int sizeX, int sizeY, 
                    float azimuth, float elevation, float beamWidth, float sectorWidth);
    AntennaArray *getAntennaArray();


    void sendSymbol(QVector<TransportBlock> tbContainer);

    void mapDmrs();
    // OFDM transmission Scheme
    void qamModulator();
    void ofdmModulator();
    void transmitThroughChannnel(RadioChannel *channel);
    void ofdmDemodulator();
    void equalization();
    void qamDemodulator();
};

#endif // PHYSICAL_H
