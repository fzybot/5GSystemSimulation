#ifndef UEPHYSICAL_H
#define UEPHYSICAL_H
#include "src/equipment/antenna/Beam.h"

#include <QVector>
#include <QMap>


class UePhysical
{

public:
    UePhysical();
public:
    QMap<Beam *, double> rsrp_best_beams;
    QMap<Beam *, double> rssi_best_beams;
    QMap<Beam *, double> distance_best_beams;
    QMap<Beam *, double> pathlos_best_beams;
    QMap<Beam *, double> sinr_best_beams;

public:
    QMap<Beam *, double> &get_rsrp_best_beams() { return rsrp_best_beams;}
    QMap<Beam *, double> &get_rssi_best_beams() { return rssi_best_beams;}
    QMap<Beam *, double> &get_distance_best_beams() { return distance_best_beams;}
    QMap<Beam *, double> &get_pathlos_best_beams() { return pathlos_best_beams;}
    QMap<Beam *, double> &get_sinr_best_beams() { return sinr_best_beams;}

};

#endif // UEPHYSICAL_H
