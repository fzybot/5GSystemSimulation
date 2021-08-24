#pragma once

#include "src/protocols/mac_layer/MacEntity.h"

class Scheduler;

class CellMacEntity : public MacEntity
{
private:
    Scheduler *scheduler_;

public:
    CellMacEntity();

    void createScheduler();
    Scheduler *getScheduler();
};
