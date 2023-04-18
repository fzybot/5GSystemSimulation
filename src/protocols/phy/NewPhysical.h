#pragma once

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

class NewPhysical
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
    
public:
    NewPhysical();
};

