#ifndef SCHEDCONFIGS_H
#define SCHEDCONFIGS_H

typedef struct {
    int sinr;
    int bufferSize;
    int cqi;
    int mcs;
    int mOrder;
    double codeRate;
    int nPrb;
    int tbs;
    int reCce;
} sched_ue_info;

#endif // SCHEDCONFIGS_H
