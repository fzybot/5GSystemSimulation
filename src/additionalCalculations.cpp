#include "additionalCalculations.h"

#include <cmath>


double sum_dBm(double dbm1, double dbm2)
{
    double sum;
    if (dbm1 < dbm2) {
        sum = dbm1 + 10 * std::log10(1 + std::pow(10, (dbm2 - dbm1) / 10));
    } else {
        sum = dbm2 + 10 * std::log10(1 + std::pow(10, (dbm1 - dbm2) / 10));
    }
    return sum;
}
