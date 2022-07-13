#include "Bandwidth.h"

#include <QDebug>
#include <QPair>



Bandwidth::Bandwidth(QString fr, QString band, int scs, bool cp, double ulBw,
                     double dlBw, int ulOffset, int dlOffset, int mimoIndex, bool tddTrue)
{
    if(tddTrue == true) {
        tdd_ = true;
        // TODO: Check the specification for TDD bandwidth calculation based
        // on Dl and UL bandwidths
    }
    else {
        ulBandwidth_ = ulBw;
        dlBandwidth_ = dlBw;
    }
    _mimoIndex = mimoIndex;
    bandwidth_ = dlBw;
    tdd_ = tddTrue;
    frequencyRange_ = fr;
    operatingBand_ = band;
    carrierFreq_ = (NR_OPERATING_BAND_DL_HIGH[band] + NR_OPERATING_BAND_DL_LOW[band]) / 2;
    subcarrierSpacing_ = scs;
    _normalCpType = cp;
    ulOffsetBw_ = ulOffset;
    dlOffsetBw_ = dlOffset;
    setNumberOfPRB(PRBs_for_BW[fr][scs][dlBw]);
    ulSubChannels_.clear();
    dlSubChannels_.clear();
    calculateSampleRate();

    // TODO: Check the correct subchannel calculation for DL and UL
    for(int i = ulOffset; i < ulOffset + PRBs_for_BW[fr][scs][ulBw]; ++i) {
        ulSubChannels_.push_back(NR_OPERATING_BAND_UL_LOW[band] + (i + 0.18));
    }

    for(int i = dlOffset; i < dlOffset + PRBs_for_BW[fr][scs][dlBw]; ++i) {
        dlSubChannels_.push_back(NR_OPERATING_BAND_DL_LOW[band] + (i + 0.18));
    }
}

void Bandwidth::configResourceGrid(bool normalCp, int scs, int nRb)
{

}

QString Bandwidth::getFrequencyRange()
{
    return frequencyRange_;
}

QString Bandwidth::getBand()
{
    return operatingBand_;
}

double Bandwidth::getCarrierFreq()
{
    return carrierFreq_;
} 

double Bandwidth::getUlBandwidth()
{
    return ulBandwidth_;
}

double Bandwidth::getDlBandwidth()
{
    return dlBandwidth_;
}

double Bandwidth::getBandwidth()
{
    return bandwidth_;
}

int Bandwidth::getSCS()
{
    return subcarrierSpacing_;
}

bool &Bandwidth::getCpType()
{
    return _normalCpType;
}

void Bandwidth::setFftSize(int size)
{
    _fftSize = size;
}

int Bandwidth::getFftSize()
{
    return _fftSize;
}

void Bandwidth::calculateSampleRate()
{
    _sampleRate = getFftSize() * getSCS() * 1000;
}

int Bandwidth::getSampleRate()
{
    return _sampleRate;
}


void Bandwidth::setNumberOfPRB(int number)
{
    numPRB_ = number;
    calculateSizeRbg();
}

int Bandwidth::getNumberOfPRB()
{
    return numPRB_;
}

void Bandwidth::setCoresetSize(int nOFDM, int nPRBs)
{
    sizeCORESET_.first = nOFDM;
    sizeCORESET_.second = nPRBs;
}

QPair<int, int> &Bandwidth::getCoresetSize()
{
    return sizeCORESET_;
}

// <  38.214 - Table 5.1.2.2.1-1: Nominal RBG size P, Table 6.1.2.2.1-1: Nominal RBG size P >
void Bandwidth::calculateSizeRbg()
{
    int nPrb = getNumberOfPRB();

    if (nPrb >= 1 && nPrb <= 36) {
        sizeRbg_ = 2;
    } else if (nPrb >= 37 && nPrb <= 72) {
        sizeRbg_ = 4;
    } else if (nPrb >= 73 && nPrb <= 144) {
        sizeRbg_ = 8;
    } else if (nPrb >= 145 && nPrb <= 275) {
        sizeRbg_ = 16;
    }  
}

void Bandwidth::setRsrp(double rsrp)
{
    _rsrp = rsrp;
}

void Bandwidth::setRsrq(double rsrq)
{
    _rsrq = rsrq;
}

void Bandwidth::setSinr(double sinr)
{
    _sinr = sinr;
}

double Bandwidth::getRsrq()
{
    return _rsrq;
}

double Bandwidth::getRsrp()
{   
    return _rsrp;
}

double Bandwidth::getSinr()
{
    return _sinr;
}


void Bandwidth::print()
{
    qDebug() << "Bandwidth information:";
    if (tdd_ == true) {
        qDebug() << "Time Division Duplex:" << tdd_;
    }
    else {
        qDebug() << "Frequency Division Duplex:" << true;
    }

    qDebug() << "Frequency Range:" << frequencyRange_;
    qDebug() << "Operating band:" << operatingBand_;
    qDebug() << "Subcarrier Spacing:" << subcarrierSpacing_;
    qDebug() << "DL Bandwidth:" << frequencyRange_;
    qDebug() << "UL Bandwidth:" << frequencyRange_;
    qDebug() << "DL Subchannels:";
    for(int i = 0; i < (int)dlSubChannels_.size(); ++i){
        qDebug() << dlSubChannels_[i];
    }
    qDebug() << "UL Subchannels:";
    for(int i = 0; i < (int)ulSubChannels_.size(); ++i){
        qDebug() << ulSubChannels_[i];
    }
}
