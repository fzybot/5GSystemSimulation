#ifndef BANDWIDTH_H
#define BANDWIDTH_H

/*
 * This class represernts the transmittion principles per cell
 * based on 3GPP TS 38.101
 */

#include <QMap>

// first element is the bandwidth in MHz, second one is the corresponding
//number of RBs
const static QMap<double, int> RBs_for_BW =
{
    { 1.4, 6 },
    { 3, 15 },
    { 5, 25 },
    { 10, 50 },
    { 15, 75 },
    { 20, 100 }
};

class Bandwidth
{
public:
    Bandwidth();


public:

};

#endif // BANDWIDTH_H
