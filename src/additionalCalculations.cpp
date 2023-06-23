#include "additionalCalculations.h"
#include "src/equipment/antenna/Beam.h"

#include <cmath>
#include <vector>
#include <QMap>
#include <QDebug>


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

bool cmp(std::pair<Beam*, double>& a,
        std::pair<Beam*, double>& b)
{
    return a.second < b.second;
}

void sortMap(QMap<Beam*, double>& M)
{
 
    // Declare vector of pairs
    std::vector<std::pair<Beam*, double> > A;
 
    // Copy key-value pair from Map
    // to vector of pairs
//    for (auto& it : M) {
//        A.push_back(it);
//    }
 
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);
 
    // Print the sorted value
    for (auto& it : A) {
 
        qDebug() << it.first << ' ' << it.second;
    }
}
