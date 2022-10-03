#ifndef PHYCONFIGS_H
#define PHYCONFIGS_H

#include <QString>
#include <QVector>

typedef struct {
    QString fr;
    QString band;
    int numerologyIndex;
    bool cpType;
    int ulBw;
    int dlBw;
} conf_band;

typedef struct {
    QVector<int> nOfdm;
    int nPrb;
    int startPrb;
    int frameNum; // '-1' means 'each'
    int subframeNum; // '-1' means 'each'
} conf_coreset;

typedef struct {
    int startSubcarrier;
    int stepSubcarrier;
    int startSymbol;
    int stepSymbol;
    int nDmrsPerRb;
    int frameNum;    // '-1' means 'each'
    int subframeNum; // '-1' means 'each'
} conf_dmrs;

typedef struct {
    int index;
    int nPdsch;
    int nDmrs;
    int nCoreset;
} info_prb;

#endif // PHYCONFIGS_H
