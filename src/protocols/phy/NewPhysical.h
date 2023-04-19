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

private:
    AntennaArray *_antennaArray;
    conf_band bandConfig;

public:
    NewPhysical();
    NewPhysical(int test);
};

