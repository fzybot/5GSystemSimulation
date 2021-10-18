#include "Scheduler.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/mac_layer/CellMacEntity.h"

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
    updateAvailableNumPRB( cell_->getPhyEntity()->getBandwidthContainer()[0][0]->getNumberOfPRB() );
    // qDebug() << "Number of PRBs --->" << getNumPRB();
    // qDebug() << "Number of TBS: "<< cell_->getMacEntity()->getTransportBlockContainer().length();

    timeDomainScheduling(userEquipmentContainer);
    frequencyDomainScheduling(timeQueue_);
}

void Scheduler::timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer)
{
    timeQueue_->clear();
    qDebug() << "Starting time scheduling-->";
    qDebug() <<"    "<<"Number of UE-->" << userEquipmentContainer->length();
    for (auto ue : *userEquipmentContainer) {
        if (ue->getBSR() != false && ue->getMeasurementGap() != true && ue->getDRX() != true) {
            timeQueue_->push_back(ue);
        }
    }
    qDebug() <<"    "<< "Number of UE Scheduled in time-->" << timeQueue_->length();
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
    freqQueue_->clear();
    qDebug() << "Scheduler::roundRobin::Starting frequency diomain scheduling (ROUND ROBIN)-->";
    for (auto timeUE: *userEquipmentContainer) {
        qDebug() <<"    "<<"UE sinr --->"<< timeUE->getSINR();
        //getCell()->getMacEntity();
    }
}

void Scheduler::propotionalFair(QVector<UserEquipment*> *userEquipmentContainer)
{

}

void Scheduler::updateAvailableNumPRB(int nPRB)
{
    nAvailablePRB_ = nPRB;
}

int Scheduler::getAvailableNumPRB()
{
    return nAvailablePRB_;
}

void Scheduler::setCell(Cell *cell)
{
    cell_ = cell;
}

Cell *Scheduler::getCell()
{
    return cell_;
}

