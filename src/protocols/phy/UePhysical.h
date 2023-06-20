#ifndef UEPHYSICAL_H
#define UEPHYSICAL_H
#include "src/equipment/antenna/Beam.h"

#include <QVector>
#include <map>


class UePhysical
{

public:
    UePhysical();
public:

    std::map<Beam*, double> bestBeams;

};

#endif // UEPHYSICAL_H
