#include "Scheduler.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Cell.h"
#include "src/protocols/phy/Physical.h"
#include "src/protocols/phy/Channel/Bandwidth.h"
#include "src/protocols/bearers/RadioBearer.h"

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
        ue->getBearerContainer()[0][0]->getQoSProfile()->showProfile();
    }

    timeDomainScheduling(userEquipmentContainer);
    frequencyDomainScheduling(userEquipmentContainer);
}

void Scheduler::timeDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer)
{
    qDebug() << "Starting time scheduling-->";
}

void Scheduler::frequencyDomainScheduling(QVector<UserEquipment*> *userEquipmentContainer)
{

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
