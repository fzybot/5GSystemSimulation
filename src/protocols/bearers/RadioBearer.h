#pragma once
#include "src/protocols/bearers/Bearer.h"

class RadioBearer : public Bearer
{
public:
    enum class RadioBearerType
    {
      SRB0,
      SRB1,
      SRB2,
      DRB
    };

private:
    RadioBearer::RadioBearerType type_;

public:
    RadioBearer();
    RadioBearer(int id);

    void createDefaultBearer(int id);
    void createRadioBearer(RadioBearerType type);
};
