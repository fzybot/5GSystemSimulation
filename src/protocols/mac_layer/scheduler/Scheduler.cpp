#include "Scheduler.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Bandwidth.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/mac_layer/CellMacEntity.h"
#include "src/protocols/mac_layer/AMC/AMCEntity.h"

#include <QDebug>
#include <QVector>
#include <QRandomGenerator>

Scheduler::Scheduler(Cell *cell, Scheduler::SchedulingAlgorithm algo)
{
    cell_ = nullptr;
    firstQueue_ = new QVector<UserEquipment *>;
    timeQueue_ = new QVector<UserEquipment *>;
    freqQueue_ = new QVector<UserEquipment *>;

    setCell(cell);
    setAlgorithm(algo);
}

void Scheduler::setAlgorithm(Scheduler::SchedulingAlgorithm algo)
{
    algorithm_ = algo;
}

Scheduler::SchedulingAlgorithm Scheduler::getAlgorithm()
{
    return algorithm_;
}

void Scheduler::doSchedule(QVector<UserEquipment*> *userEquipmentContainer)
{
    qDebug() << "Current Cell Id------>" << getCell()->getEquipmentId();
    int carrAggIndex = 0;
    int mimoIndex = 0;
    int nPrb = getCell()->getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex]->getNumberOfPRB();
    int nOfdmCoreset = getCell()->getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex]->getCoreset().nOfdm.length();
    int nPrbCoreset = getCell()->getPhyEntity()->getBandwidthContainer()[carrAggIndex][mimoIndex]->getCoreset().nPrb;
    int coresetSize = nOfdmCoreset * nPrbCoreset * 12; // 12 subcarriers in 1 RB
    int slot = getCell()->getLocalOwnTimeSlot();
    updateAvailableNumPRB(nPrb);
    updateAvailableNumCoresetRe(coresetSize);
    // qDebug() << "Cp Type: " << getCell()->getPhyEntity()->getBandwidthContainer()[0][0]->getCpType();
    // qDebug() << "Scheduler::doSchedule::Number of RE CORESET --->" << coresetSize;
    // qDebug() << "Number of PRBs --->" << getNumPRB();
    // qDebug() << "Number of TBS: "<< cell_->getMacEntity()->getTransportBlockContainer().length();

    timeDomainScheduling(userEquipmentContainer);
    if (getTimeDomainQueue()->length() > 0){
        frequencyDomainScheduling(getTimeDomainQueue(), nPrb, coresetSize);
        transmitTbThroughPhysical(slot);
        getTimeDomainQueue()[0][0]->showDataTransmitted();
    }
}

QVector<UserEquipment *> *Scheduler::getTimeDomainQueue()
{
    return timeQueue_;
}

void Scheduler::timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer)
{
    qDebug() << "Starting time scheduling-->";
    timeQueue_->clear();
    for (auto ue : *userEquipmentContainer) {
        if (ue->getBSR() == true && ue->getMeasurementGap() != true && ue->getDRX() != true) {
            timeQueue_->push_back(ue);
        }
    }
}

void Scheduler::schedule(QVector<UserEquipment*> *userEquipmentContainer)
{
    timeDomainScheduling(userEquipmentContainer);
    if (getTimeDomainQueue()->length() > 0){
        frequencyDomainScheduling(getTimeDomainQueue(), getBwContainer());
    }
}

void Scheduler::frequencyDomainScheduling( QVector<UserEquipment*> *userEquipmentContainer, 
                                    QVector< QVector<Bandwidth*> > &bwContainerMimoCarrAgg)
{
    switch (algorithm_)
    {
    case Scheduler::SchedulingAlgorithm::ROUND_ROBIN:
        roundRobin(userEquipmentContainer, bwContainerMimoCarrAgg);
        break;
    }
}

void Scheduler::roundRobin(QVector<UserEquipment*> *userEquipmentContainer, 
                QVector< QVector<Bandwidth*> > &bwContainerMimoCarrAgg)
{
    for(auto carrAgg : bwContainerMimoCarrAgg){
        for (auto bwMimo : carrAgg){
            distributePerBw(userEquipmentContainer, bwMimo);
        }
    }
}

void Scheduler::distributePerBw(QVector<UserEquipment*> *userEquipmentContainer, Bandwidth* bw)
{
    for (auto timeUe : *userEquipmentContainer)
    {
        //int nDmrs = bw
        fillUeSchedInfo(timeUe);
        int remainingPrb = bw->getNumberOfPRB();
        int mOrder = getUeSchedInfo().mOrder;
        double codeRate = getUeSchedInfo().codeRate;
        int nPrbPerUe = getUeSchedInfo().nPrb;
        int tbs = getUeSchedInfo().tbs;
        int nReCce = getUeSchedInfo().reCce;

        qDebug() << "distribute --> " << tbs;
    }
}

void Scheduler::frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize)
{
    switch (algorithm_)
    {
    case Scheduler::SchedulingAlgorithm::ROUND_ROBIN:
        roundRobin(userEquipmentContainer, nPrb, coresetSize);
        break;

    case Scheduler::SchedulingAlgorithm::PROPOTIONAL_FAIR:
        propotionalFair(userEquipmentContainer, nPrb, coresetSize);
        break;
    }
}

void Scheduler::roundRobin(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize)
{
    qDebug() << "Scheduler::roundRobin::Starting frequency diomain scheduling (ROUND ROBIN)-->";
    qDebug() << "Scheduler::roundRobin::userEquipmentContainer length -->" << userEquipmentContainer->length();
    int utilizedPrb = 0;
    int size = 0;
    int codeRateSize = 0;
    for (auto timeUe : *userEquipmentContainer)
    {
        fillUeSchedInfo(timeUe);
        int mOrder = getUeSchedInfo().mOrder;
        double codeRate = getUeSchedInfo().codeRate;
        int nPrbPerUe = getUeSchedInfo().nPrb;
        int tbs = getUeSchedInfo().tbs;
        int nReCce = getUeSchedInfo().reCce;

        if( (nPrb -  nPrbPerUe) > 0 && (coresetSize - nReCce) > 0 ) {
            // Create TBS object with packets inside
            for (auto bearer : *timeUe->getBearerContainer()){
                fillTbWithPackets(bearer, tbs, codeRate, nPrbPerUe, mOrder);
            }

            //size += localTbs_.getSizeWoCodeRate();
            //codeRateSize += localTbs_.getSize();
            // "Distribute" the resources for UE
            // qDebug() <<"    "<< "Scheduler::roundRobin::Remaining PRBs before distribution -->" << nRemainingPrb_;
            nPrb -= nPrbPerUe;
            utilizedPrb += nPrbPerUe;
            coresetSize -= nReCce;

            // qDebug() <<"    "<< "Scheduler::roundRobin::UE Id --->"<< timeUE->getEquipmentId();
            // qDebug() <<"    "<< "Scheduler::roundRobin::UE SINR|CQI|MSC|TBS|CodeRate --->"<< ueSINR << cqi << mcs << tbs << codeRate;
            // qDebug() <<"    "<< "Scheduler::roundRobin::UE Buffer Size --->"<< timeUE->getBufferSize();
            // qDebug() <<"    "<< "Scheduler::roundRobin::UE allocated PRBs --->"<< nPrbPerUe;
            // qDebug() <<"    "<< "Scheduler::roundRobin::Remaining PRBs -->" << nRemainingPrb_;
            // qDebug() <<"    "<< "Scheduler::roundRobin::Remaining CCE REs -->" << nRemainingCoresetRe_;
            // getCell()->getMacEntity()->getAMCEntity()->showParameters();
        }
        //localTbs_.clear();
    }
    int slot = getCell()->getLocalOwnTimeSlot();
    // qDebug() <<"    "<< "Scheduler::roundRobin::addCountPrbUtilized -->" << utilizedPrb;
}

void Scheduler::propotionalFair(QVector<UserEquipment*> *userEquipmentContainer, int nPrb, int coresetSize)
{

}

QVector<TransportBlock> Scheduler::transmitTbThroughPhysical(int slot)
{
    //showTransportBlockContainer();
    int localIndex = 0;
    int neededIndex = 0;
    QVector<TransportBlock> errorContainer;
    QVector<TransportBlock> succContainer;
    QVector<TransportBlock> currentSlotContainer;
    for(auto value : getTransportBlockContainer()){
        TransportBlock transmitted = transportBlockContainer_.dequeue();
        if(transmitted.getSlotToTransmit() == slot){
            currentSlotContainer.append(transmitted);
            int transmissionProbability = QRandomGenerator::global()->bounded(1, 100);
            if (transmissionProbability > 10) {
                transmitted.setSlotTransmitted(slot);
                //getCell()->getPhyEntity()->
                succContainer.append(transmitted);
            } else {
                transmitted.setHarqStatus(true);
                int rndHarqSlot = QRandomGenerator::global()->bounded(4, 8);
                transmitted.setSlotToTransmit(slot+rndHarqSlot);
                errorContainer.append(transmitted);
            }
        } else {
            errorContainer.append(transmitted);
        }
    }
    countCell(succContainer, slot);
    errorTransmissionToQueue(errorContainer);

    return succContainer;
}

void Scheduler::fillUeSchedInfo(UserEquipment *ue)
{
    getUeSchedInfo().sinr = ue->getSinrPerBandidth(0);
    getUeSchedInfo().bufferSize = ue->getBufferSize();
    getUeSchedInfo().cqi = getCqiFromSinr(getUeSchedInfo().sinr);
    getUeSchedInfo().mcs = getMcsFromCqi(getUeSchedInfo().cqi);
    getUeSchedInfo().mOrder = getMOrderFromMcs(getUeSchedInfo().mcs);
    getUeSchedInfo().codeRate = getCodeRateFromMcs(getUeSchedInfo().mcs);
    getUeSchedInfo().nPrb = calculateOptimalNumberOfPrbPerUe(getUeSchedInfo().mcs, _maxPrbPerUe, 2, getUeSchedInfo().bufferSize);
    //getUeSchedInfo().tbs = getTbs(getUeSchedInfo().mcs, getUeSchedInfo().nPrb, nLayers_, nCoresetRe_);
    // 1 [CCE] = 6 [REG]; 1 [RE]G = 12 [subcarrires] x 1 [OFDM symbol]
    getUeSchedInfo().reCce = calcAggLevel(getUeSchedInfo().sinr) * 6 * 12; 

}

QVector<QVector<Bandwidth *>> &Scheduler::getBwContainer()
{
    return getCell()->getPhyEntity()->getBandwidthContainer();
}

sched_ue_info &Scheduler::getUeSchedInfo()
{
    return _ueInfo;
}

int Scheduler::getCqiFromSinr(int sinr)
{
    return getCell()->getMacEntity()->getAMCEntity()->getCQIFromSinr (sinr);
}

int Scheduler::getMcsFromCqi(int cqi)
{
    return getCell()->getMacEntity()->getAMCEntity()->getMCSFromCQI(cqi);
}

int Scheduler::getMOrderFromMcs(int mcs)
{
    return getCell()->getMacEntity()->getAMCEntity()->getModulationOrderFromMCS(mcs);
}

double Scheduler::getCodeRateFromMcs(int mcs)
{
    return getCell()->getMacEntity()->getAMCEntity()->getCodeRateFromMcs(mcs);
}

int Scheduler::getTbs(int mcs, int nPrb, int nDmrs, int nLayers, int nCoresetRe)
{
    return getCell()->getMacEntity()->getAMCEntity()->getTBSizeFromMCS(mcs, nPrb, nDmrs, nLayers, nCoresetRe);
}

void Scheduler::updateAvailableNumPRB(int nPRB)
{
    nPrb_ = nPRB;
    nRemainingPrb_ = nPRB;
}

int Scheduler::getRemainingNumPRB()
{
    return nRemainingPrb_;
}

void Scheduler::updateAvailableNumCoresetRe(int coresetRe)
{
    nCoresetRe_ = coresetRe;
    nRemainingCoresetRe_ = coresetRe;
}

int Scheduler::getRemainingNumCoresetRe()
{
    return nRemainingCoresetRe_;
}

int Scheduler::calculateOptimalNumberOfPrbPerUe(int mcs, int maxPrb, int nDmrs, int ueBuffer)
{
    int min = ueBuffer;
    int maxPossiblePrb = 1;
    int tbs;
    for (int i = 1; i <= maxPrb; i++) {
        tbs = getCell()->getMacEntity()->getAMCEntity()->getTBSizeFromMCS(mcs, i, nDmrs, nLayers_, nCoresetRe_);
        if (abs(ueBuffer - tbs) < min) {
            min = abs(ueBuffer - tbs);
            maxPossiblePrb = i;
        }
    }
    return maxPossiblePrb;
}

// TODO: more accurate calculation in case of Bit Array for data
void Scheduler::fillTbWithPackets(RadioBearer *bearer, int tbsSize, double codeRate, int nPrbPerUe, int mOrder)
{
    int index = 0;
    int lTbs = 0;
    QVector<Packet*> packetsToDelete;
    packetsToDelete.clear();
    TransportBlock localTbs_;
    localTbs_.setUserEquipment(bearer->getUserEquipment());
    for (auto packet : bearer->getPacketsContainerCurrentSlot(getCell()->getLocalOwnTimeSlot()))
    {
        if(nRemainingPrb_ > 0 && nRemainingCoresetRe_ > 0) {
            lTbs = localTbs_.getSize() + (int)(packet->getSize() / codeRate);
            //qDebug() <<"    "<< "Scheduler::fillTbWithPackets:: tbs container --> " << tbsSize << lTbs << localTbs_.getSize() << (int)(packet->getSize()/codeRate);
            // TODO: if lTbs < tbsSize !!! make an exeption
            if (lTbs <= tbsSize)
            {
                localTbs_.appendPacket(packet, (int)(packet->getSize()/codeRate));
                packetsToDelete.append(packet);
                qDebug() << "    "<< "Scheduler::fillTbWithPackets:: TBS --> " << lTbs;
            }
            else
            {
                break; // TBS is fulfilled
            }
        }
        index++;
    }
    if (localTbs_.getSize() != 0){
        int slot = getCell()->getLocalOwnTimeSlot();
        localTbs_.setNumberOfPrb(nPrbPerUe);
        localTbs_.setSlotToTransmit(slot);
        localTbs_.setSlotInitialized(slot);
        localTbs_.setModulationOrder(mOrder);
        addToTbsContainer(localTbs_);
        bearer->deletePackets(packetsToDelete);
    }
}

void Scheduler::addToTbsContainer(TransportBlock tb)
{
    getTransportBlockContainer().enqueue(tb);
}

// TODO: need more accurate calculation
int Scheduler::calcAggLevel(double sinr)
{
    int aggLevel = 1;
    if (sinr >= 14) {
        aggLevel = 1;
    } else if (sinr < 14 && sinr >= 8.72) {
        aggLevel = 2;
    } else if (sinr < 8.72 && sinr >= 4.92) {
        aggLevel = 4;
    } else if (sinr < 4.92 && sinr >= -3) {
        aggLevel = 8;
    } else {
        aggLevel = 16;
    }
    return aggLevel;
}

void Scheduler::errorTransmissionToQueue(QVector<TransportBlock> &errorContainer)
{   
    for (auto tb : errorContainer)
    {
        addToTbsContainer(tb);
    }
}

QQueue<TransportBlock> &Scheduler::getTransportBlockContainer()
{
    return transportBlockContainer_;
}

void Scheduler::setCell(Cell *cell)
{
    cell_ = cell;
}

Cell *Scheduler::getCell()
{
    return cell_;
}

void Scheduler::countCell(QVector<TransportBlock> tbContainer, int slot)
{

    int utilizedPrb = 0;
    int codeRateSize = 0;
    int pureData = 0;

    for (auto tb : tbContainer)
    {
        utilizedPrb += tb.getNumberOfPrb();
        codeRateSize += tb.getSize();
        pureData += tb.getSizeWoCodeRate();
        countUe(tb, slot);
    }
    getCell()->addCountPrbUtilized(slot, utilizedPrb);
    getCell()->addCountTbTransmitted(slot, codeRateSize);
    getCell()->addCountDataTransmitted(slot, pureData);
}

void Scheduler::countUe(TransportBlock tb, int slot)
{

    tb.getUserEquipment()->addCountDataTransmitted(slot, tb.getSizeWoCodeRate());
}

void Scheduler::showTransportBlockContainer()
{
    for(auto tb : getTransportBlockContainer()){
        qDebug() << "    "<< "Scheduler::showTransportBlockContainer:: tb-->" << tb.getSize() << tb.getSlotToTransmit();
    }
}

