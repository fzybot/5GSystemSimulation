#include "Bandwidth.h"

#include <QDebug>



Bandwidth::Bandwidth(QString fr, QString band, int scs, double ulBw,
                     double dlBw, int ulOffset, int dlOffset, bool tddTrue)
{
    if(tddTrue == true) {
        tddTrue = true;
        // TODO: Check the specification for TDD bandwidth calculation based
        // on Dl and UL bandwidths
    }
    else {
        this->m_ulBandwidth = ulBw;
        this->m_dlBandwidth = dlBw;
    }

    m_tdd = tddTrue;
    m_frequencyRange = fr;
    m_operatingBand = band;
    m_subcarrierSpacing = scs;
    m_ulOffsetBw = ulOffset;
    m_dlOffsetBw = dlOffset;

    m_ulSubChannels.clear();
    m_dlSubChannels.clear();

    // TODO: Check the correct subchannel calculation for DL and UL
    for(int i = ulOffset; i < ulOffset + PRBs_for_BW["FR1"][scs][ulBw]; ++i) {
        m_ulSubChannels.push_back(NR_OPERATING_BAND_UL_LOW[band] + (i + 0.18));
    }

    for(int i = dlOffset; i < dlOffset + PRBs_for_BW["FR1"][scs][dlBw]; ++i) {
        m_dlSubChannels.push_back(NR_OPERATING_BAND_DL_LOW[band] + (i + 0.18));
    }

}

void Bandwidth::print()
{
    qDebug() << "Bandwidth information:" << Qt::endl;
    if (m_tdd == true) {
        qDebug() << "Time Division Duplex:" << m_tdd << Qt::endl;
    }
    else {
        qDebug() << "Frequency Division Duplex:" << true << Qt::endl;
    }

    qDebug() << "Frequency Range:" << m_frequencyRange << Qt::endl;
    qDebug() << "Operating band:" << m_operatingBand << Qt::endl;
    qDebug() << "Subcarrier Spacing:" << m_subcarrierSpacing << Qt::endl;
    qDebug() << "DL Bandwidth:" << m_frequencyRange << Qt::endl;
    qDebug() << "UL Bandwidth:" << m_frequencyRange << Qt::endl;
    qDebug() << "DL Subchannels:" << Qt::endl;
    for(int i = 0; i < (int)m_dlSubChannels.size(); ++i){
        qDebug() << m_dlSubChannels[i] << Qt::endl;
    }
    qDebug() << "UL Subchannels:" << Qt::endl;
    for(int i = 0; i < (int)m_ulSubChannels.size(); ++i){
        qDebug() << m_ulSubChannels[i] << Qt::endl;
    }
    qDebug() << Qt::endl;
}
