
#include "CellMacEntity.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"
#include "src/equipment/Cell.h"

#include "src/debug.h"


CellMacEntity::CellMacEntity()
{
    debug("Cell Mac Entity: MAC Entity is created");
    configMacEntity();
}

void CellMacEntity::createScheduler(Scheduler::SchedulingAlgorithm algo)
{
    scheduler_ = new Scheduler();
    scheduler_->setAlgorithm(algo);
    scheduler_->setCell(getDevice());
}

Scheduler *CellMacEntity::getScheduler()
{
    return scheduler_;
}

void CellMacEntity::schedule(Cell *cell)
{
    getScheduler()->doSchedule(cell->getUserEquipmentContainer());
}
