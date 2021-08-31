
#include "CellMacEntity.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"

#include "src/debug.h"


CellMacEntity::CellMacEntity()
{
    debug("gNodeB Mac Entity: MAC Entity is created");
    configMacEntity();
    createScheduler();
}

void CellMacEntity::createScheduler()
{
    scheduler_ = new Scheduler();
}