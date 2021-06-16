#ifndef BANDWIDTH_H
#define BANDWIDTH_H

/*
 * This class represernts the transmittion principles per cell
 * based on 3GPP TS 38.101
 */

#include <QMap>
#include <QString>


//first element is the bandwidth in MHz, second one is the corresponding
//number of RBs
// For example: RBs_for_BW["FR2"][60][100] means the number of PRBs
//
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

class Bandwidth
{
public:
    Bandwidth() = default;
    Bandwidth(double ulBw, double dlBw, int ulOffset, int dlOffset,
              bool tddTrue = false);


private:

    double m_ulBandwidth;
    double m_dlBandwidth;

    int m_ulOffsetBw;
    int m_dlOffsetBw;

    QVector<double> m_dlSubChannels;
    QVector<double> m_ulSubChannels;

    int m_subcarrierSpacing;

};

#endif // BANDWIDTH_H
