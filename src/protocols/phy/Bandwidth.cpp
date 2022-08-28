#include "Bandwidth.h"
#include "src/protocols/phy/ResourceGrid.h"

#include <QDebug>
#include <QPair>



Bandwidth::Bandwidth(QString fr, QString band, int scs, bool cp, double ulBw,
                     double dlBw, int ulOffset, int dlOffset, int mimoIndex, int carrierAggIndex, bool tddTrue)
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
    _carrierAggIndex = carrierAggIndex;
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

void Bandwidth::configResourceGrid()
{
    getResouceGrid().configResourceGrid(this->getCpType(), this->getNumberOfPRB());
    qDebug() << "Resource grid is configured";
}

ResourceGrid &Bandwidth::getResouceGrid()
{
    return _resourceGrid;
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

void Bandwidth::setCoreset(QVector<int> nOFDM, int nPRBs, int startPrb, int frameN, int subframeN)
{
    getCoreset().nOfdm = nOFDM;
    getCoreset().nPrb = nPRBs;
    getCoreset().startPrb = startPrb;
    getCoreset().frameNum = frameN;
    getCoreset().subframeNum = subframeN;
}

conf_coreset &Bandwidth::getCoreset()
{
    return _coreset;
}

void Bandwidth::setDmrs(int startSub, int stepSub, int startSymb, int stepSymb, int frameN, int subframeN)
{
    getDmrs().startSubcarrier = startSub;
    getDmrs().stepSubcarrier = stepSub;
    getDmrs().startSymbol = startSymb;
    getDmrs().stepSymbol = stepSymb;
    getDmrs().frameNum = frameN;
    getDmrs().subframeNum = subframeN;
}
conf_dmrs &Bandwidth::getDmrs()
{
    return _dmrs;
}

int Bandwidth::getNDmrs()
{
    return getDmrs().nDmrsPerRb;
}

void Bandwidth::fillIndexes()
{
    int cp = 12;
    if(getCpType()){
        cp = 14;
    }
    _dmrsIndexes.resize(cp);
    _dataIndexes.resize(cp);
    _coresetIndexes.resize(cp);
    _containerPrb.resize(getNumberOfPRB());
    qDebug() << "numPrb --> " << getNumberOfPRB() * 12;
    qDebug() << "numPrb coreset --> " << getCoreset().nPrb * 12;
    for (int sc = getDmrs().startSubcarrier; sc < getNumberOfPRB() * 12; sc += getDmrs().stepSubcarrier)
        {
            _dmrsIndexes[getDmrs().startSymbol].push_back(sc);
            _containerPrb[floor(sc / 12)].index = floor(sc / 12);
            _containerPrb[floor(sc / 12)].nDmrs++;
        }
    int i = 1;
    for (int symb = 0; symb < cp; symb++)
    {
        if (symb == ( i * (getDmrs().startSymbol + getDmrs().stepSymbol)) )
        {
            i++;
            for (int sc = getDmrs().startSubcarrier; sc < getNumberOfPRB() * 12; sc += getDmrs().stepSubcarrier)
            {
                _dmrsIndexes[symb].push_back(sc);
                _containerPrb[floor(sc / 12)].index = floor(sc / 12);
                _containerPrb[floor(sc / 12)].nDmrs++;
                
            }
        }
        for (auto coresetOfdm : getCoreset().nOfdm)
        {
            if (symb == coresetOfdm)
            {
                if (getDmrsIndexes()[symb].length() > 0){
                    int j = 0;
                    for (int sc = 0; sc < getNumberOfPRB() * 12; sc++)
                    {
                        // bw->setCoreset({0, 1}, bw->getNumberOfPRB() - 20, 1);
                        // bw->setDmrs(1, 3, 1, 3);
                        //qDebug() << "dmrs length() Indexes --> " << getDmrsIndexes()[symb][j] << " sc --> " << sc;
                        if ( (sc != getDmrsIndexes()[symb][j]) ){
                            if ( (sc >= (getCoreset().startPrb * 12)) && (sc < (getCoreset().nPrb + getCoreset().startPrb) * 12) ){
                                _coresetIndexes[symb].push_back(sc);
                                _containerPrb[floor(sc / 12)].index = floor(sc / 12);
                                _containerPrb[floor(sc / 12)].nCoreset++;
                                //qDebug() << "symbol --> " << symb << " sc indexes --> " << sc << " prb indexes floor --> " << floor(sc / 12);
                            }
                            else
                            {
                                _dataIndexes[symb].push_back(sc);
                                _containerPrb[floor(sc / 12)].index = floor(sc / 12);
                                _containerPrb[floor(sc / 12)].nPdsch++;
                            }
                        } else if (j < getDmrsIndexes()[symb].length() - 1){
                            j++;
                        }
                    }
                } else {
                    for (int sc = 0; sc < getNumberOfPRB() * 12; sc++)
                    {
                        if ( (sc >= (getCoreset().startPrb * 12)) && (sc < (getCoreset().nPrb + getCoreset().startPrb) * 12) ){
                            _coresetIndexes[symb].push_back(sc);
                            _containerPrb[floor(sc / 12)].index = floor(sc / 12);
                            _containerPrb[floor(sc / 12)].nCoreset++;
                        } else {
                            _dataIndexes[symb].push_back(sc);
                            _containerPrb[floor(sc / 12)].index = floor(sc / 12);
                            _containerPrb[floor(sc / 12)].nPdsch++;
                        }
                    }
                }
            }
        }
        if (getDataIndexes()[symb].length() == 0){
            if (getDmrsIndexes()[symb].length() > 0){
                int j = 0;
                for (int sc = 0; sc < getNumberOfPRB() * 12; sc++)
                {
                    //qDebug() << "dmrs length() Indexes --> " << getDmrsIndexes()[symb][j] << " sc --> " << sc;
                    if ( (sc != getDmrsIndexes()[symb][j])){
                        _dataIndexes[symb].push_back(sc);
                        _containerPrb[floor(sc / 12)].index = floor(sc / 12);
                        _containerPrb[floor(sc / 12)].nPdsch++;
                    } else if (j < getDmrsIndexes()[symb].length() - 1){
                        j++;
                    }
                }
            } else {
                for (int sc = 0; sc < getNumberOfPRB() * 12; sc++)
                {
                    _dataIndexes[symb].push_back(sc);
                    _containerPrb[floor(sc / 12)].index = floor(sc / 12);
                    _containerPrb[floor(sc / 12)].nPdsch++;
                }
            }
        }
    }
    // for(auto dmrs : getDmrsIndexes()){
    //     qDebug() << "dmrs --> " << dmrs.length();
    // }
    // for(auto data : getDataIndexes()){
    //     qDebug() << "data --> " << data.length();
    // }
    // for(auto coreset : getCoresetIndexes()){
    //     qDebug() << "coreset --> " << coreset.length();
    // }
    // for(auto prb : getPrbInfo()){
    //     qDebug() << "Prb info --> ";
    //     qDebug() << "   " << "Prb index --> " << prb.index;
    //     qDebug() << "   " << "Prb nDmrs --> " << prb.nDmrs;
    //     qDebug() << "   " << "Prb nPdsch --> " << prb.nPdsch;
    //     qDebug() << "   " << "Prb nCoreset --> " << prb.nCoreset;
    // }
}

QVector<QVector<int>> &Bandwidth::getDmrsIndexes()
{
    return _dmrsIndexes;
}

QVector<QVector<int>> &Bandwidth::getDataIndexes()
{
    return _dataIndexes;
}

QVector<QVector<int>> &Bandwidth::getCoresetIndexes()
{
    return _coresetIndexes;
}

void Bandwidth::fillPrbInfo()
{
    for (int sc = 0; sc < getNumberOfPRB() * 12; sc++)
    {
        
    }
}

QVector<info_prb> &Bandwidth::getPrbInfo()
{
    return _containerPrb;
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
