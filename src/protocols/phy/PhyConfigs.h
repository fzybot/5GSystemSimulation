#ifndef PHYCONFIGS_H
#define PHYCONFIGS_H

#include <QString>

typedef struct {
    QString fr;
    QString band;
    int numerologyIndex;
    bool cpType;
    int ulBw;
    int dlBw;
} conf_band;

typedef struct {
    int nOfdm;
    int nPrb;
    int startPrb;
    int frameNum = -1; // '-1' means 'each'
    int subframeNum = -1; // '-1' means 'each'
} conf_coreset;

typedef struct {
    int startSubcarrier;
    int stepSubcarrier;
    int startSymbol;
    int stepSymbol;
    int frameNum = -1; // '-1' means 'each'
    int subframeNum = -1; // '-1' means 'each'
} conf_dmrs;

#endif // PHYCONFIGS_H
