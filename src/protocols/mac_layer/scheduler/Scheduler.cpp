#include "Scheduler.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/mac_layer/CellMacEntity.h"
#include "src/protocols/mac_layer/AMC/AMCEntity.h"

#include <QDebug>
#include <QVector>

Scheduler::Scheduler()
{
    cell_ = nullptr;
    firstQueue_ = new QVector<UserEquipment *>;
    timeQueue_ = new QVector<UserEquipment *>;
    freqQueue_ = new QVector<UserEquipment *>;
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
    qDebug() << "Current Cell Id------>" << cell_->getEquipmentId();
    int nPrb = cell_->getPhyEntity()->getBandwidthContainer()[0][0]->getNumberOfPRB();
    QPair<int, int> coreset = cell_->getPhyEntity()->getBandwidthContainer()[0][0]->getCoresetSize();
    int coresetSize = coreset.first * coreset.second * 12; // 12 subcarriers in 1 RB
    updateAvailableNumPRB(nPrb);
    updateAvailableNumCoresetRe(coresetSize);
    qDebug() << "Scheduler::doSchedule::Number of RE CORESET --->" << coresetSize;
    // qDebug() << "Number of PRBs --->" << getNumPRB();
    // qDebug() << "Number of TBS: "<< cell_->getMacEntity()->getTransportBlockContainer().length();

    timeDomainScheduling(userEquipmentContainer);
    if (timeQueue_->length() > 0){
        frequencyDomainScheduling(timeQueue_);
    }
}

void Scheduler::timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer)
{
    qDebug() << "Starting time scheduling-->";
    timeQueue_->clear();
    for (auto ue : *userEquipmentContainer) {
        if (ue->getBSR() != false && ue->getMeasurementGap() != true && ue->getDRX() != true) {
            timeQueue_->push_back(ue);
        }
    }
}

void Scheduler::frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer)
{
    switch (algorithm_)
    {
    case Scheduler::SchedulingAlgorithm::ROUND_ROBIN:
        roundRobin(userEquipmentContainer);
        break;

    case Scheduler::SchedulingAlgorithm::PROPOTIONAL_FAIR:
        propotionalFair(userEquipmentContainer);
        break;
    }
}

void Scheduler::roundRobin(QVector<UserEquipment*> *userEquipmentContainer)
{
    qDebug() << "Scheduler::roundRobin::Starting frequency diomain scheduling (ROUND ROBIN)-->";
    qDebug() << "Scheduler::roundRobin::userEquipmentContainer length -->" << userEquipmentContainer->length();
    int utilizedPrb = 0;
    int size = 0;
    int codeRateSize = 0;
    for (auto timeUE : *userEquipmentContainer)
    {

        double ueSINR = timeUE->getSINR();
        int ueBufferSize = timeUE->getBufferSize();
        int cqi = getCell()->getMacEntity()->getAMCEntity()->getCQIFromSinr (ueSINR);
        int mcs = getCell()->getMacEntity()->getAMCEntity()->getMCSFromCQI(cqi);
        double codeRate = getCell()->getMacEntity()->getAMCEntity()->getCodeRateFromMcs(mcs);
        int maxNPrbPerUe = 30;
        int nPrbPerUe =  calculateOptimalNumberOfPrbPerUe(mcs, nRemainingPrb_, ueBufferSize); // TODO: think about nRemainingPrb_
        int tbs = getCell()->getMacEntity()->getAMCEntity()->getTBSizeFromMCS(mcs, nPrbPerUe, nLayers_, nCoresetRe_);
        int nReCce = calcAggLevel(ueSINR) * 6 * 12; // 1 [CCE] = 6 [REG]; 1 [RE]G = 12 [subcarrires] x 1 [OFDM symbol]

        if( (nRemainingPrb_ -  nPrbPerUe) > 0 && (nRemainingCoresetRe_ - nReCce) > 0 ) {
            // Create TBS object with packets inside
            fillTbWithPackets(timeUE, tbs, codeRate);
            size += localTbs_.getSizeWoCodeRate();
            codeRateSize += localTbs_.getSize();
            // "Distribute" the resources for UE
            qDebug() <<"    "<< "Scheduler::roundRobin::Remaining PRBs before distribution -->" << nRemainingPrb_;
            nRemainingPrb_ -= nPrbPerUe;
            utilizedPrb += nPrbPerUe;
            nRemainingCoresetRe_ -= nReCce;

            qDebug() <<"    "<< "Scheduler::roundRobin::UE Id --->"<< timeUE->getEquipmentId();
            qDebug() <<"    "<< "Scheduler::roundRobin::UE SINR|CQI|MSC|TBS|CodeRate --->"<< ueSINR << cqi << mcs << tbs << codeRate;
            qDebug() <<"    "<< "Scheduler::roundRobin::UE Buffer Size --->"<< timeUE->getBufferSize();
            qDebug() <<"    "<< "Scheduler::roundRobin::UE allocated PRBs --->"<< nPrbPerUe;
            qDebug() <<"    "<< "Scheduler::roundRobin::Remaining PRBs -->" << nRemainingPrb_;
            qDebug() <<"    "<< "Scheduler::roundRobin::Remaining CCE REs -->" << nRemainingCoresetRe_;
            //getCell()->getMacEntity()->getAMCEntity()->showParameters();
        }
    }

    qDebug() <<"    "<< "Scheduler::roundRobin::addCountPrbUtilized -->" << utilizedPrb;
    getCell()->addCountPrbUtilized(utilizedPrb);
    getCell()->addCountTbTransmitted(codeRateSize);
    getCell()->addCountDataTransmitted(size);
}

void Scheduler::propotionalFair(QVector<UserEquipment*> *userEquipmentContainer)
{

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

int Scheduler::calculateOptimalNumberOfPrbPerUe(int mcs, int maxPrb, int ueBuffer)
{
    int min = ueBuffer;
    int maxPossiblePrb = 1;
    int tbs;
    for (int i = 1; i <= maxPrb; i++) {
        tbs = getCell()->getMacEntity()->getAMCEntity()->getTBSizeFromMCS(mcs, i, nLayers_, nCoresetRe_);
        if (abs(ueBuffer - tbs) < min) {
            min = abs(ueBuffer - tbs);
            maxPossiblePrb = i;
        }
    }
    return maxPossiblePrb;
}

// TODO: more accurate calculation in case of Bit Array for data
void Scheduler::fillTbWithPackets(UserEquipment *user, int tbsSize, double codeRate)
{
    localTbs_.clear();
    int index = 0;
    int lTbs = 0;
    QVector<int> deletePackets;
    for (auto packet : user->getPacketsContainer())
    {
        if(nRemainingPrb_ > 0 && nRemainingCoresetRe_ > 0) {
            lTbs = localTbs_.getSize() + (int)(packet->getSize()/codeRate) ;
            qDebug() <<"    "<< "Scheduler::fillTbWithPackets:: tbs container --> " << tbsSize << lTbs << localTbs_.getSize() << (int)(packet->getSize()/codeRate);
            // TODO: if lTbs < tbsSize !!! make an exeption
            if (lTbs <= tbsSize)
            {
                localTbs_.appendPacket(packet, (int)(packet->getSize()/codeRate));
                packet->setSlotTransmitted(getCell()->getLocalOwnTimeSlot());
                deletePackets.append(index);
                // qDebug() << "    "<< "Scheduler::fillTbWithPackets:: packet transmitted slot --> " << packet->getSlotTransmitted();
            }
            else
            {
                break; // TBS is fulfilled
            }
        }
        index++;
    }

    // for (int i = 0; i < deletePackets.size(); i++){
    //     for (int j = 0; j < user->getPacketsContainer().size(); j++){
    //         qDebug() << "DELETE --> " << user->getPacketsContainer().size();
    //         user->getPacketsContainer().remove(deletePackets[i]);
    //     }
    // }
        // Before that fill with zeros
    //localTbs_.setSize(tbsSize);
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

void Scheduler::setCell(Cell *cell)
{
    cell_ = cell;
}

Cell *Scheduler::getCell()
{
    return cell_;
}

