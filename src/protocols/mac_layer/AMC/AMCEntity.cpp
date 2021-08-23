
#include <QVector>
#include <QtMath>
#include <QDebug>

#include "AMCEntity.h"
#include "AMCParameters.h"
#include "src/protocols/mac_layer/AMC/miesmEffSINR.h"

AMCEntity::AMCEntity()
{

}

AMCEntity::~AMCEntity()
{

}

int AMCEntity::GetCQIFromEfficiency (double Efficiency)
{
    int cqi = 1; // == CQIIndex[0]
    while (EfficiencyForCQIIndex[cqi] < Efficiency && cqi <= 14) {
        cqi++;
    }
    return cqi;
}

int AMCEntity::GetCQIFromSinr (double sinr)
{
    int cqi = 1; // == CQIIndex[0]
    while (SINRForCQIIndex[cqi] <= sinr && cqi <= 14) {
        cqi++;
    }
    return cqi;
}

double AMCEntity::GetSinrFromCQI (int cqi)
{
    double sinr = SINRForCQIIndex[cqi-1]+0.1;
    return sinr;
}

int AMCEntity::GetMCSFromCQI (int cqi)
{
    return MapCQIToMCS [cqi-1];
}

int AMCEntity::GetCQIFromMCS (int mcs)
{
    int cqi = 0;
    for (int i=0; i<15; i++) {
        if (mcs <= MapCQIToMCS[i]) {
            cqi = i+1;
            break;
        }
    }
    return cqi;
}

int AMCEntity::GetMCSIndexFromEfficiency(double efficiency)
{
    int mcs = 1;
    while (EfficiencyForMCSIndex[mcs] < efficiency && mcs < 30) {
        mcs++;
    }
    return mcs;
}

int AMCEntity::GetTBSizeFromMCS (int mcs)
{
    return TransportBlockSizeTable[0][McsToItbs[mcs]];
}

int AMCEntity::GetTBSizeFromMCS (int mcs, int nbRBs)
{
    int itbs = McsToItbs[mcs];
    return (TransportBlockSizeTable[nbRBs - 1][itbs]);
}

int AMCEntity::GetTBSizeFromMCS (int mcs, int nbRBs, int nbLayers)
{
    int itbs = McsToItbs[mcs];
    int tbs;
    int baselineTbs;
    switch(nbLayers) {
        case 1:
            tbs = TransportBlockSizeTable[nbRBs - 1][itbs];
            break;

        case 2:
            if( nbRBs < 56) {
                tbs = TransportBlockSizeTable[nbRBs * 2 - 1][itbs];
            }
            else {
                baselineTbs = TransportBlockSizeTable[nbRBs - 1][itbs];
                // TODO: optimize using dicotomic search, because data is already ordered
                for (int i = 0; i < 120; i++) {
                    if( TbsL1ToL2Translation[0][i] == baselineTbs) {
                        tbs = TbsL1ToL2Translation[1][i];
                        break;
                    }
                }
            }
            break;

        case 3:
            if( nbRBs < 37) {
                tbs = TransportBlockSizeTable[nbRBs * 3 - 1][itbs];
            }
            else {
                baselineTbs = TransportBlockSizeTable[nbRBs - 1][itbs];
                // TODO: optimize using dicotomic search, because data is already ordered
                for (int i = 0; i < 134; i++) {
                    if( TbsL1ToL3Translation[0][i] == baselineTbs) {
                        tbs = TbsL1ToL3Translation[1][i];
                        break;
                    }
                }
            }
            break;

        case 4:
            if( nbRBs < 28) {
                tbs = TransportBlockSizeTable[nbRBs * 4 - 1][itbs];
            }
            else
            {
                baselineTbs = TransportBlockSizeTable[nbRBs - 1][itbs];
                // TODO: optimize using dicotomic search, because data is already ordered
                for (int i = 0; i < 142; i++) {
                    if( TbsL1ToL4Translation[0][i] == baselineTbs) {
                        tbs = TbsL1ToL4Translation[1][i];
                        break;
                    }
                }
            }
            break;

        default:
            qDebug() << "Invalid number of layers for TBS calculation: " << nbLayers;
            exit(1);
            break;
    }
    return tbs;
}


int AMCEntity::GetTBSizeFromMCS (int mcs1, int mcs2, int nbRBs, int rank)
{
    int tbs;
    switch(rank)
    {
        case 1:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 1);
            break;
        case 2:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 1) + GetTBSizeFromMCS (mcs2, nbRBs, 1);
            break;
        case 3:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 1) + GetTBSizeFromMCS (mcs2, nbRBs, 2);
            break;
        case 4:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 2) + GetTBSizeFromMCS (mcs2, nbRBs, 2);
            break;
        case 5:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 2) + GetTBSizeFromMCS (mcs2, nbRBs, 3);
            break;
        case 6:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 3) + GetTBSizeFromMCS (mcs2, nbRBs, 3);
            break;
        case 7:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 3) + GetTBSizeFromMCS (mcs2, nbRBs, 4);
            break;
        case 8:
            tbs = GetTBSizeFromMCS (mcs1, nbRBs, 4) + GetTBSizeFromMCS (mcs2, nbRBs, 4);
            break;
        default:
            qDebug() << "Invalid rank for TBS calculation: " << rank;
            exit(1);
            break;
    }
    return tbs;
}

double AMCEntity::GetEfficiencyFromCQI (int cqi)
{
    int mcs = GetMCSFromCQI (cqi);
    int bits = GetTBSizeFromMCS (mcs,1);
    //eff = rate / bandwidth
    double eff = (bits/0.001)/180000.;
    return eff;
}


int AMCEntity::GetModulationOrderFromMCS(int mcs)
{
    return ModulationSchemeForMCSIndex[mcs];
}


int AMCEntity::GetMCSFromSinrVector(const QVector<double> &sinr)
{
    int mcs = 0;
    for (int modulationOrder=2; modulationOrder<7; modulationOrder+=2) {
        double estimated_effsinr = GetMiesmEffectiveSinr(sinr, modulationOrder);
        int estimated_cqi = GetCQIFromSinr(estimated_effsinr);
        int estimated_mcs = GetMCSFromCQI(estimated_cqi);
        int estimated_modulation_order = GetModulationOrderFromMCS(estimated_mcs);
        if(estimated_modulation_order == modulationOrder) {
            mcs = estimated_mcs;
        }
    }
    return mcs;
}

QVector<int> AMCEntity::CreateCqiFeedbacks (QVector<double> sinr)
{
    QVector<int> cqi;
    for (auto sinr_ : sinr) {
        int cqi_ = GetCQIFromSinr (sinr_);
        cqi.push_back (cqi_);
    }
    return cqi;
}
