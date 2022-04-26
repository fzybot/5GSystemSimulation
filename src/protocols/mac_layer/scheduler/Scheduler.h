#pragma once

#include "src/protocols/mac_layer/TransportBlock.h"

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
    QQueue<TransportBlock> transportBlockContainer_;   // Transport Block container to PHY layer
    //TransportBlock          localTbs_;

private:
    int nLayers_ = 2;
    int nPrb_ = 0;
    int nRemainingPrb_ = 0;
    int nCoresetRe_ = 0;
    int nRemainingCoresetRe_ = 0;
    int nMaxScheuledUe_ = 5;
    int currentScheduledUe = 0;
    int nMinPrbPerUe_ = 1;

public:
    Scheduler(Cell *cell, Scheduler::SchedulingAlgorithm algo);

    void doSchedule(QVector<UserEquipment*> *userEquipmentContainer);

    void setCell(Cell *cell);
    Cell *getCell();

    void setAlgorithm(SchedulingAlgorithm algo);
    SchedulingAlgorithm getAlgorithm();

    void timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer);
    void frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize);

    // Scheduling algorithms
    void roundRobin(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize);
    void propotionalFair(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize);
    void besetCqi(QVector<UserEquipment *> *userEquipmentContainer, int nPrb, int coresetSize);

    QVector<TransportBlock> transmitTbThroughPhysical(int slot);

    // Support methods
    void updateAvailableNumPRB(int nPRB);
    int getRemainingNumPRB();
    void updateAvailableNumCoresetRe(int coresetRe);
    int getRemainingNumCoresetRe();
    int calculateOptimalNumberOfPrbPerUe(int mcs, int maxPrb, int ueBuffer);
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
