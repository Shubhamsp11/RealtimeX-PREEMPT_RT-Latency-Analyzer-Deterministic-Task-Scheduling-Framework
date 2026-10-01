#ifndef RMSCHEDULER_H
#define RMSCHEDULER_H

#include "Scheduler.h"

class RMScheduler : public Scheduler {
public:
    RMScheduler(TaskManager* tm, LatencyAnalyzer* la) : Scheduler(tm, la) {}
    void schedule(int durationMs) override;
};

#endif
