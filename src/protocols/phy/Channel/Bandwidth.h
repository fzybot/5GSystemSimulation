/*
 * This class represernts the transmittion principles per cell
 * based on 3GPP TS 38.101
 */


#pragma once


#include <QMap>
#include <QString>

/*
 * The 5G NR operating bands list according to TS 38.104 Table 5.2-1\2.
 * The FR1 and FR2 are in one QMap list. FR2 starts from "n257".
 */

const static QMap <QString ,  float> NR_OPERATING_BAND_UL_LOW =
{
    {"n1", 1920},
    {"n3", 1710},
    {"n7", 2500},
    {"n257", 26500},

};
const static QMap <QString ,  float> NR_OPERATING_BAND_UL_HIGH =
{
    {"n1", 1980},
    {"n3", 1785},
    {"n7", 2570},
    {"n257", 29500},

};
const static QMap <QString ,  float> NR_OPERATING_BAND_DL_LOW =
{
    {"n1", 2110},
    {"n3", 1805},
    {"n7", 2620},
    {"n257", 26500},

};
const static QMap <QString ,  float> NR_OPERATING_BAND_DL_HIGH =
{
    {"n1", 2170},
    {"n3", 1880},
    {"n7", 2690},
    {"n257", 29500},

};

/*
 * The first element is the bandwidth in MHz, second one is the corresponding
 * number of RBs.
 * For example: RBs_for_BW["FR2"][60][100] means the number of PRBs for FR2,
 * SCS = 60 kHz, Bandwidth = 100 MHz, which is equal to 132 PRBs.
 */
const static QMap<QString, QMap<int, QMap<int, int> > > PRBs_for_BW =
{
    { "FR1", { {15, { {5, 25},
                      {10, 52},
                      {15, 79},
                      {20, 106},
                      {25, 133},
                      {30, 160},
                      {40, 216},
                      {50, 270},
                    }
               },
               {30, { {5, 11},
                      {10, 24},
                      {15, 38},
                      {20, 51},
                      {25, 65},
                      {30, 78},
                      {40, 106},
                      {50, 133},
                      {60, 162},
                      {70, 189},
                      {80, 217},
                      {90, 245},
                      {100, 273},
                    }
               },
               {60, { {10, 11},
                      {15, 18},
                      {20, 24},
                      {25, 31},
                      {30, 38},
                      {40, 51},
                      {50, 65},
                      {60, 79},
                      {70, 93},
                      {80, 107},
                      {90, 121},
                      {100, 135},
                    }
                },
            }
    },
    { "FR2", { {60, { {50, 66},
                      {100, 132},
                      {200, 264},
                    }
               },
               {120, { {50, 32},
                      {100, 66},
                      {200, 132},
                      {400, 264},
                    }
               },
            }
    },
};

/*
 * This class models the bandwidth used for the transmission
 * in a particular cell.
 * See information on TS 38.104 Table 5.2-1\2
 */

class Bandwidth
{
private:
    bool tdd_;
    QString frequencyRange_;
    QString operatingBand_;
    double carrierFreq_;
    double ulBandwidth_;
    double dlBandwidth_;
    double bandwidth_;

    int ulOffsetBw_;
    int dlOffsetBw_;

    QVector<double> dlSubChannels_;
    QVector<double> ulSubChannels_;

    int subcarrierSpacing_;
    int numPRB_;

public:
    Bandwidth() = default;
    Bandwidth(QString fr, QString band, int scs, double ulBw, double dlBw,
              int ulOffset, int dlOffset, bool tddTrue = true);

    int getNumberOfPRB();
    void print();
};
