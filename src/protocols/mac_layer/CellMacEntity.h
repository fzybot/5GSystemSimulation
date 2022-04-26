#pragma once

#include "src/protocols/mac_layer/MacEntity.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"
#include "src/equipment/Cell.h"

class CellMacEntity : public MacEntity
{
private:
    Cell *_cell;
    Scheduler *_scheduler;

public:
    CellMacEntity(Cell *cell);

    void createScheduler(Scheduler::SchedulingAlgorithm algo);
    Scheduler *getScheduler();
    void schedule();
};
