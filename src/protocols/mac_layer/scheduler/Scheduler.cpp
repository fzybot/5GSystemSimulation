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
    firstQueue_ = new QVector<UserEquipment*>;
    timeQueue_ = new QVector<UserEquipment*>;
    freqQueue_ = new QVector<UserEquipment*>;
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
    int nPrb;
    nPrb = cell_->getPhyEntity()->getBandwidthContainer()[0][0]->getNumberOfPRB();
    updateAvailableNumPRB(nPrb);
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
    // qDebug() <<"    "<<"Number of UE-->" << userEquipmentContainer->length();
    // qDebug() <<"    "<< "Number of UE Scheduled in time-->" << timeQueue_->length();
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
    for (auto timeUE: *userEquipmentContainer) {
        int ueSINR = timeUE->getSINR();
        int ueBufferSize = timeUE->getBufferSize();
        int cqi = getCell()->getMacEntity()->getAMCEntity()->GetCQIFromSinr (ueSINR);
        int mcs = getCell()->getMacEntity()->getAMCEntity()->GetMCSFromCQI(cqi);
        int nPrbPerUe = calculateOptimalNumberOfPrbPerUe(mcs, nPrb_, ueBufferSize);
        int tbs = getCell()->getMacEntity()->getAMCEntity()->getTBSizeFromMCS(mcs, nPrbPerUe, nLayers_);

        qDebug() <<"    "<<"UE Id --->"<< timeUE->getEquipmentId();
        qDebug() <<"    "<<"UE SINR|CQI|MSC|TBS --->"<< ueSINR << cqi << mcs << tbs;
        qDebug() <<"    "<<"UE Buffer Size --->"<< timeUE->getBufferSize();
        qDebug() <<"    "<<"UE allocated PRBs --->"<< nPrbPerUe;
        qDebug() <<"    "<<"mark"<< "1";
        getCell()->getMacEntity()->getAMCEntity()->showParameters();
    }
}

void Scheduler::propotionalFair(QVector<UserEquipment*> *userEquipmentContainer)
{

}

void Scheduler::updateAvailableNumPRB(int nPRB)
{
    nPrb_ = nPRB;
    nRemainingPrb_ = nPRB;
}

int Scheduler::getAvailableNumPRB()
{
    return nRemainingPrb_;
}

int Scheduler::calculateOptimalNumberOfPrbPerUe(int mcs, int maxPrb, int ueBuffer)
{
    int min = ueBuffer;
    int maxPossiblePrb = 1;
    int tbs;
    for (int i = 1; i <= maxPrb; i++) {
        tbs = getCell()->getMacEntity()->getAMCEntity()->getTBSizeFromMCS(mcs, i, nLayers_);
        if (abs(ueBuffer - tbs) < min) {
            min = abs(ueBuffer - tbs);
            maxPossiblePrb = i;
        }
    }
    return maxPossiblePrb;
}

void Scheduler::setCell(Cell *cell)
{
    cell_ = cell;
}

Cell *Scheduler::getCell()
{
    return cell_;
}

