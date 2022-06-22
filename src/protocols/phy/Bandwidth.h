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

/*
 * This class models the bandwidth used for the transmission
 * in a particular cell.
 * See information on TS 38.104 Table 5.2-1\2
 */

class Bandwidth
{
private:
    bool    tdd_;
    QString frequencyRange_;
    QString operatingBand_;
    double  carrierFreq_;
    double  ulBandwidth_;
    double  dlBandwidth_;
    int     ulOffsetBw_;
    int     dlOffsetBw_;
    double  bandwidth_;
    int     subcarrierSpacing_;
    int     numPRB_;
    bool    _normalCpType = true;

    int     sizeRbg_;

    double      _sinr = 0;
    double      _rsrp = 0;
    double      _rsrq = 0;

    // first - number of OFDM Symbols
    // second - number of RBs (1 RB = 12 REs)
    int _coresetStart = 0;
    QPair<int, int> sizeCORESET_;
    QVector<QVector<int>> _coresetPattern;

    int _dmrsStartFreq = 1, _dmrsStepFreq = 3, _dmrsStartSymb = 0, _dmrsStepSymb = 3;   

    // Each element should looks like: [PRB Index, RSRP own, Interference Neighbour] 
    QVector<QVector<int>> v;
    QVector<double> dlSubChannels_;
    QVector<double> ulSubChannels_;


public:
    Bandwidth() = default;
    Bandwidth(QString fr, QString band, int scs,bool cp, double ulBw, double dlBw,
              int ulOffset, int dlOffset, bool tddTrue = true);

    QString getFrequencyRange();
    QString getBand();
    double  getCarrierFreq();
    double  getUlBandwidth();
    double  getDlBandwidth();
    double  getBandwidth();
    int     getSCS();
    bool    &getCpType();

    void setNumberOfPRB(int number);
    int getNumberOfPRB();

    void configResourceGrid(bool normalCp, int scs, int nRb);
    void fillRsrpPerPrb(QVector<int> &signalPower);
    void fillInterferencePerPrb(QVector<int> &interference);

    void setCoresetSize(int nOFDM, int nPRBs);
    QPair<int, int> &getCoresetSize();

    void calculateSizeRbg();

    void setRsrp(double rsrp);
    void setRsrq(double rsrq);
    void setSinr(double sinr);
    double getRsrq();
    double getRsrp();
    double getSinr();

    void print();
};
