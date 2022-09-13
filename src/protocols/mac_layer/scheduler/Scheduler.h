#pragma once

#include "src/protocols/mac_layer/TransportBlock.h"
#include "src/protocols/phy/ResourceGrid.h"
#include "src/protocols/mac_layer/scheduler/schedConfigs.h"

#include <QVector>
#include <QQueue>

class UserEquipment;
class Cell;
class gNodeB;

class Scheduler
{
public:
    enum class SchedulingAlgorithm
    {
      ROUND_ROBIN,
      PROPOTIONAL_FAIR,
      BEST_CQI,
      SOMETHING_ELSE,
    };

protected:
    SchedulingAlgorithm         algorithm_;
    Cell                        *cell_;
    QVector<UserEquipment*>    *firstQueue_;   // ? don't know why yet
    QVector<UserEquipment*>    *timeQueue_;    // Time domain  candidates
    QVector<UserEquipment*>    *freqQueue_;    // Frequency domain candidates

    QVector<Packet*>        packetContainer_;           // Packet container to schedule
    QQueue<TransportBlock>  transportBlockContainer_;   // Transport Block container to PHY layer
    //TransportBlock          localTbs_;

private:
    sched_ue_info _ueInfo;
    int nLayers_ = 1;
    int nPrb_ = 0;
    int nRemainingPrb_ = 0;
    int nCoresetRe_ = 0;
    int nRemainingCoresetRe_ = 0;
    int nMaxScheuledUe_ = 20;
    int currentScheduledUe = 0;
    int nMinPrbPerUe_ = 1;
    int _maxPrbPerUe = 100000;

    ResourceGrid _virtualResourceGrid;

public:
    Scheduler(Cell *cell, Scheduler::SchedulingAlgorithm algo);

    void setCell(Cell *cell);
    Cell *getCell();

    void setAlgorithm(SchedulingAlgorithm algo);
    SchedulingAlgorithm getAlgorithm();

    QVector<UserEquipment *> *getTimeDomainQueue();

    void schedule(QVector<UserEquipment*> *userEquipmentContainer);
    void timeDomainScheduling(QVector<UserEquipment *> *userEquipmentContainer);
    void frequencyDomainScheduling( QVector<UserEquipment*> *userEquipmentContainer, 
                                QVector< QVector<Bandwidth*> > &bwContainerMimoCarrAgg);
    // Scheduling algorithms [try.1.0.0]
    void roundRobin(QVector<UserEquipment*> *userEquipmentContainer, 
                    QVector< QVector<Bandwidth*> > &bwContainerMimoCarrAgg);



    void doSchedule(QVector<UserEquipment*> *userEquipmentContainer);
    void frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize);

    // Scheduling algorithms [OLD]
    void roundRobin(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize);
    void propotionalFair(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize);
    void besetCqi(QVector<UserEquipment *> *userEquipmentContainer, int nPrb, int coresetSize);

    QVector<TransportBlock> transmitTbThroughPhysical(int slot);

    // Support methods
    void distributePerBw(QVector<UserEquipment*> *userEquipmentContainer, Bandwidth* bw);
    void fillUeSchedInfo(UserEquipment *ue);
    sched_ue_info &getUeSchedInfo();
    QVector<QVector<Bandwidth *>> &getBwContainer();
    int getCqiFromSinr(int sinr);
    int getMcsFromCqi(int cqi);
    int getMOrderFromMcs(int mcs);
    double getCodeRateFromMcs(int mcs);
    int getTbs(int mcs, int nPrb, int nDmrs, int nLayers, int nCoresetRe_);

    void updateAvailableNumPRB(int nPRB);
    int getRemainingNumPRB();
    void updateAvailableNumCoresetRe(int coresetRe);
    int getRemainingNumCoresetRe();
    int calculateOptimalNumberOfPrbPerUe(int mcs, int maxPrb, int nDmrs, int ueBuffer);
    void fillTbWithPackets(RadioBearer *bearer, int tbsSize, double codeRate, int nPrb, int mOrder);
    void packetsToTbs();
    int calcAggLevel(double sinr);

    QQueue<TransportBlock> &getTransportBlockContainer();
    void showTransportBlockContainer();
    void addToTbsContainer(TransportBlock tb);

    void errorTransmissionToQueue(QVector<TransportBlock> &errorContainer);

    void packetSegmentation(Packet *packet, int neededSize);

    // TODO: finish these methods
    void checkMeasGap(QVector<UserEquipment*> *userEquipmentContainer);
    void checkDRX(QVector<UserEquipment*> *userEquipmentContainer);
    void checkTransmitSlot(QVector<UserEquipment *> *userEquipmentContainer);

    void addToQueue(int id);

    void countCell(QVector<TransportBlock> tb, int slot);
    void countUe(TransportBlock tb, int slot);
};
