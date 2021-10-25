#pragma once

#include "src/protocols/mac_layer/MacEntity.h"
#include "src/protocols/mac_layer/scheduler/Scheduler.h"


class CellMacEntity : public MacEntity
{
private:
    Scheduler *scheduler_;

public:
    CellMacEntity();

    void createScheduler(Scheduler::SchedulingAlgorithm algo);
    Scheduler *getScheduler();
    void schedule(Cell *cell);
};
