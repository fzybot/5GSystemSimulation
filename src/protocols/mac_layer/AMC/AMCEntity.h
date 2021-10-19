#pragma once

#include <QVector>

class AMCEntity
{
private:
//     double* SINRForCQIIndex;
    int MCSIndexTableNumber_ = 1;

public:
    AMCEntity();
    virtual ~AMCEntity();

    int GetCQIFromSinr (double sinr);
    int GetMCSFromCQI (int cqi);
    int getTBSizeFromMCS(int mcs, int nPRB);


// ----- [ LTE ] -------------------------------------------------------------------------------------------------------
    int GetCQIFromEfficiency (double sinr);
    int GetMCSIndexFromEfficiency(double spectralEfficiency);
    int GetCQIFromMCS (int mcs);
    double GetEfficiencyFromCQI(int cqi);
    double GetSinrFromCQI (int cqi);
    int GetModulationOrderFromMCS(int mcs);
    int GetMCSFromSinrVector(const QVector<double> &sinr);

    QVector<int> CreateCqiFeedbacks (QVector<double> sinr);

    // FOR LTE
    // int GetTBSizeFromMCS (int mcs);
    // int GetTBSizeFromMCS (int mcs, int nbRBs);
    // int GetTBSizeFromMCS (int mcs, int nbRBs, int nbLayers);
    // int GetTBSizeFromMCS (int mcs1, int mcs2, int nbRBs, int rank);
};
