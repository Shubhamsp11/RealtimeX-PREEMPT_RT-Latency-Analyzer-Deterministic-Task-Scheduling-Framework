#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "TaskManager.h"
#include "LatencyAnalyzer.h"

class Scheduler {
protected:
    TaskManager* taskManager;
    LatencyAnalyzer* analyzer;

public:
    Scheduler(TaskManager* tm, LatencyAnalyzer* la) : taskManager(tm), analyzer(la) {}
    virtual ~Scheduler() {}
    
    virtual void schedule(int durationMs) = 0;
};

#endif
