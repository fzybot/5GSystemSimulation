#include "Bandwidth.h"

#include <QDebug>



Bandwidth::Bandwidth(QString fr, QString band, int scs, double ulBw,
                     double dlBw, int ulOffset, int dlOffset, bool tddTrue)
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
    bandwidth_ = dlBw;
    tdd_ = tddTrue;
    frequencyRange_ = fr;
    operatingBand_ = band;
    carrierFreq_ = (NR_OPERATING_BAND_DL_HIGH[band] + NR_OPERATING_BAND_DL_LOW[band]) / 2;
    subcarrierSpacing_ = scs;
    ulOffsetBw_ = ulOffset;
    dlOffsetBw_ = dlOffset;
    numPRB_ = PRBs_for_BW[fr][scs][dlBw];
    ulSubChannels_.clear();
    dlSubChannels_.clear();

    // TODO: Check the correct subchannel calculation for DL and UL
    for(int i = ulOffset; i < ulOffset + PRBs_for_BW[fr][scs][ulBw]; ++i) {
        ulSubChannels_.push_back(NR_OPERATING_BAND_UL_LOW[band] + (i + 0.18));
    }

    for(int i = dlOffset; i < dlOffset + PRBs_for_BW[fr][scs][dlBw]; ++i) {
        dlSubChannels_.push_back(NR_OPERATING_BAND_DL_LOW[band] + (i + 0.18));
    }
}

int Bandwidth::getNumberOfPRB()
{
    return numPRB_;
}

void Bandwidth::print()
{
    qDebug() << "Bandwidth information:" << Qt::endl;
    if (tdd_ == true) {
        qDebug() << "Time Division Duplex:" << tdd_ << Qt::endl;
    }
    else {
        qDebug() << "Frequency Division Duplex:" << true << Qt::endl;
    }

    qDebug() << "Frequency Range:" << frequencyRange_ << Qt::endl;
    qDebug() << "Operating band:" << operatingBand_ << Qt::endl;
    qDebug() << "Subcarrier Spacing:" << subcarrierSpacing_ << Qt::endl;
    qDebug() << "DL Bandwidth:" << frequencyRange_ << Qt::endl;
    qDebug() << "UL Bandwidth:" << frequencyRange_ << Qt::endl;
    qDebug() << "DL Subchannels:" << Qt::endl;
    for(int i = 0; i < (int)dlSubChannels_.size(); ++i){
        qDebug() << dlSubChannels_[i] << Qt::endl;
    }
    qDebug() << "UL Subchannels:" << Qt::endl;
    for(int i = 0; i < (int)ulSubChannels_.size(); ++i){
        qDebug() << ulSubChannels_[i] << Qt::endl;
    }
    qDebug() << Qt::endl;
}
