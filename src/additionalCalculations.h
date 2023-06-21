#pragma once
#include "src/equipment/antenna/Beam.h"

#include <QMap>


double sum_dBm(double dbm1, double dbm2);
double dBmToWatt(double dbm);
double wattTodBm(double watt);

bool cmp(std::pair<Beam*, double>& a,
        std::pair<Beam*, double>& b);
void sortMap(QMap<Beam*, double> &M);
