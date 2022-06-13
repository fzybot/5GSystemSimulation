#pragma once

#include <QVector>

#include "src/protocols/phy/OfdmSymbol.h"

class Slot
{
private:
    int _scs;
    
    QVector<OfdmSymbol> _symbolVector;

public:
    Slot();
};

