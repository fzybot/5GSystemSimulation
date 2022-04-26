
#include "CellMacEntity.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"
#include "src/equipment/Cell.h"

#include "src/debug.h"


CellMacEntity::CellMacEntity(Cell *cell)
{
    debug("Cell Mac Entity: MAC Entity is created");
    assignCell(cell);
    configMacEntity();
}

void CellMacEntity::createScheduler(Scheduler::SchedulingAlgorithm algo)
{
    _scheduler = new Scheduler(getCell(), algo);
}

Scheduler *CellMacEntity::getScheduler()
{
    return _scheduler;
}

void CellMacEntity::schedule()
{
    getScheduler()->doSchedule(getCell()->getUserEquipmentContainer());
}
