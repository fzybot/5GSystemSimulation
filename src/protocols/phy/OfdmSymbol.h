#pragma once

#include "src/protocols/phy/Slot.h"


class OfdmSymbol
{
    enum class SymbolType
    {
      NORMAL,
      EXTENDED
    };
private:


public:
    OfdmSymbol(Slot &slot);

};

