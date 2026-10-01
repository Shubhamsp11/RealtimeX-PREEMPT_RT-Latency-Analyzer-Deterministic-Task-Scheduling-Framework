#ifndef EDFSCHEDULER_H
#define EDFSCHEDULER_H

#include "Scheduler.h"

class EDFScheduler : public Scheduler {
public:
    EDFScheduler(TaskManager* tm, LatencyAnalyzer* la) : Scheduler(tm, la) {}
    void schedule(int durationMs) override;
};

#endif
