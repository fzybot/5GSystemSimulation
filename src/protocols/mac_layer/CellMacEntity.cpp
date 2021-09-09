
#include "CellMacEntity.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"

#include "src/debug.h"


CellMacEntity::CellMacEntity()
{
    debug("Cell Mac Entity: MAC Entity is created");
    dataBuffer_ = new QVector<int>;
    configMacEntity();
    createScheduler();
}

void CellMacEntity::createScheduler()
{
    scheduler_ = new Scheduler();
}