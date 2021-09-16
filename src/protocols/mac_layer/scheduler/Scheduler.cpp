#include "Scheduler.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"

#include <QDebug>
#include <QVector>

Scheduler::Scheduler()
{
    cell_ = nullptr;
    firstQueue_ = new QVector<int>;
    timeQueue_ = new QVector<int>;
    freqQueue_ = new QVector<int>;
}

void Scheduler::doSchedule(QVector<UserEquipment*> *userEquipmentContainer)
{
    qDebug() << "Current Cell Id------>" << cell_->getEquipmentId();
    int nPRB;
    
    nPRB = cell_->getPhyEntity()->getBandwidthContainer()[0][0]->getNumberOfPRB();

    qDebug() << "Number of PRBs --->" << nPRB;
    for (auto ue : *userEquipmentContainer)
    {
        addToQueue(ue->getEquipmentId());
        qDebug() << "Scheduling....UE--->" << ue->getEquipmentId();
        qDebug() << "   BufferSize....UE--->" << ue->getBufferSize();
    }

    timeDomainScheduling();
    frequencyDomainScheduling();
}

void Scheduler::setCell(Cell *cell)
{
    cell_ = cell;
}
Cell *Scheduler::getCell()
{
    return cell_;
}

void Scheduler::addToQueue(int id)
{
    firstQueue_->push_back(id);
}
