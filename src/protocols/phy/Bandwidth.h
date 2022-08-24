/*
 * This class represernts the transmittion principles per cell
 * based on 3GPP TS 38.101
 */


#pragma once

#include <QString>
#include <QPair>
#include <QVector>
#include <complex>

#include "src/protocols/phy/bandList.h"
#include "src/protocols/phy/ResourceGrid.h"
#include "src/protocols/phy/PhyConfigs.h"

/*
 * This class models the bandwidth used for the transmission
 * in a particular cell.
 * See information on TS 38.104 Table 5.2-1\2
 */

class Bandwidth
{
private:
    QString frequencyRange_;
    QString operatingBand_;
    bool    tdd_;
    int     _mimoIndex;
    int     _carrierAggIndex;
    bool    _normalCpType = true;
    double  carrierFreq_;
    double  ulBandwidth_;
    double  dlBandwidth_;
    double  bandwidth_;
    int     ulOffsetBw_;
    int     dlOffsetBw_;
    int     subcarrierSpacing_;
    int     numPRB_;
    int     sizeRbg_;
    int     _sampleRate;
    int     _fftSize = 4096;

    ResourceGrid _resourceGrid;

    double      _sinr = 0;
    double      _rsrp = 0;
    double      _rsrq = 0;

    // first - number of OFDM Symbols
    // second - number of RBs (1 RB = 12 REs)
    conf_coreset    _coreset;
    conf_dmrs       _dmrs;   

    // Each element should looks like: [PRB Index, RSRP own, Interference Neighbour] 
    QVector<QVector<int>> _dmrsIndexes;
    QVector<QVector<int>> _dataIndexes;
    QVector<QVector<int>> _coresetIndexes;

    QVector<double> dlSubChannels_;
    QVector<double> ulSubChannels_;


public:
    Bandwidth() = default;
    Bandwidth(QString fr, QString band, int scs,bool cp, double ulBw, double dlBw,
              int ulOffset, int dlOffset, int mimoIndex, int carrierAggIndex, bool tddTrue = true);

    QString getFrequencyRange();
    QString getBand();
    double  getCarrierFreq();
    double  getUlBandwidth();
    double  getDlBandwidth();
    double  getBandwidth();
    int     getSCS();
    bool    &getCpType();
    void    setFftSize(int size);
    int     getFftSize();

    void calculateSampleRate();
    int getSampleRate();

    void setNumberOfPRB(int number);
    int getNumberOfPRB();

    void configResourceGrid();
    ResourceGrid &getResouceGrid();
    void fillRsrpPerPrb(QVector<int> &signalPower);
    void fillInterferencePerPrb(QVector<int> &interference);

    void setCoreset(QVector<int> nOFDM, int nPRBs, int startPrb, int frameN = -1, int subframeN = -1);
    void setDmrs(int startSub, int stepSub, int startSymb, int stepSymb, int frameN = -1, int subframeN = -1);
    conf_coreset &getCoreset();
    conf_dmrs &getDmrs();

    void fillIndexes();
    QVector<QVector<int>> &getDmrsIndexes();
    QVector<QVector<int>> &getDataIndexes();
    QVector<QVector<int>> &getCoresetIndexes();

    void calculateSizeRbg();

    void setRsrp(double rsrp);
    void setRsrq(double rsrq);
    void setSinr(double sinr);
    double getRsrq();
    double getRsrp();
    double getSinr();

    void print();
};
