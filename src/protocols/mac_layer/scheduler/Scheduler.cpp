#include "Scheduler.h"
#include "src/equipment/UserEquipment.h"
#include "src/equipment/Cell.h"

#include <QDebug>

Scheduler::Scheduler()
{
    cell_ = nullptr;
}

void Scheduler::doSchedule(QVector<UserEquipment*> *userEquipmentContainer)
{
    qDebug() << "Current Cell------>" << cell_->getEquipmentId();
    for (auto ue : *userEquipmentContainer)
    {
        qDebug() << "Scheduling...." << ue->getEquipmentId();
    }
}

void Scheduler::setCell(Cell *cell)
{
    cell_ = cell;
}
Cell *Scheduler::getCell()
{
    return cell_;
}
