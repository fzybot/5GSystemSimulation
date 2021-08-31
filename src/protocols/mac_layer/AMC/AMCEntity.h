#pragma once

#include <QVector>

class AMCEntity
{
private:
    double* SINRForCQIIndex;
public:
    AMCEntity();
    virtual ~AMCEntity();

    int GetCQIFromEfficiency (double sinr);
    int GetMCSIndexFromEfficiency(double spectralEfficiency);
    int GetMCSFromCQI (int cqi);
    int GetCQIFromMCS (int mcs);
    int GetTBSizeFromMCS (int mcs);
    int GetTBSizeFromMCS (int mcs, int nbRBs);
    int GetTBSizeFromMCS (int mcs, int nbRBs, int nbLayers);
    int GetTBSizeFromMCS (int mcs1, int mcs2, int nbRBs, int rank);
    double GetEfficiencyFromCQI (int cqi);
    int GetCQIFromSinr (double sinr);
    double GetSinrFromCQI (int cqi);
    int GetModulationOrderFromMCS(int mcs);
    int GetMCSFromSinrVector(const QVector<double> &sinr);

    QVector<int> CreateCqiFeedbacks (QVector<double> sinr);
};
