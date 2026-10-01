#include "RMScheduler.h"
#include "TaskExecutionEngine.h"
#include <iostream>
#include <algorithm>
#include <vector>

struct Job {
    Task task;
    int releaseTime;
    int absoluteDeadline;
    int remainingTime;
    bool isDispatched;
    int actualDispatchTime;
};

void RMScheduler::schedule(int durationMs) {
    std::cout << "\n--- Running Rate Monotonic Scheduler (" << durationMs << " ms) [SIMULATION MODE] ---\n";
    analyzer->clear("RM");
    
    std::vector<Task> tasks = taskManager->getTasks();
    if (tasks.empty()) {
        std::cout << "No tasks to schedule.\n";
        return;
    }

    TaskExecutionEngine engine;
    std::vector<Job> readyQueue;

    for (int t = 0; t < durationMs; ++t) {
        // Release tasks at their periods
        for (const auto& task : tasks) {
            if (t % task.getPeriod() == 0) {
                readyQueue.push_back({task, t, t + task.getDeadline(), task.getExecutionTime(), false, -1});
            }
        }

        // Clean up finished jobs
        for (auto it = readyQueue.begin(); it != readyQueue.end(); ) {
            if (it->remainingTime <= 0) {
                it = readyQueue.erase(it);
            } else {
                ++it;
            }
        }

        if (readyQueue.empty()) continue;

        // RM Priority: Shortest Period First
        std::sort(readyQueue.begin(), readyQueue.end(), [](const Job& a, const Job& b) {
            if (a.task.getPeriod() == b.task.getPeriod()) {
                if (a.releaseTime == b.releaseTime) {
                    return a.task.getId() < b.task.getId();
                }
                return a.releaseTime < b.releaseTime; // Tie-breaker 1: earlier release
            }
            return a.task.getPeriod() < b.task.getPeriod();
        });

        Job& runningJob = readyQueue.front();

        if (!runningJob.isDispatched) {
            runningJob.isDispatched = true;
            runningJob.actualDispatchTime = t;
            long long latencyMs = t - runningJob.releaseTime;
            
            std::cout << "[" << t << "ms] " << runningJob.task.getName() << "\n";
            std::cout << "Release: " << runningJob.releaseTime << "ms\n";
            std::cout << "Dispatch: " << t << "ms\n";
            std::cout << "Latency: " << latencyMs << "ms\n";
            std::cout << "Deadline: " << runningJob.absoluteDeadline << "ms\n\n";
            
            // Dispatch to real worker thread to demonstrate C++ multithreading
            Task* tPtr = taskManager->getTaskById(runningJob.task.getId());
            if (tPtr) engine.executeTask(tPtr);
        }

        runningJob.remainingTime--;
        
        if (runningJob.remainingTime == 0) {
            int completionTime = t + 1;
            long long latencyUs = (runningJob.actualDispatchTime - runningJob.releaseTime) * 1000LL;
            bool missed = completionTime > runningJob.absoluteDeadline;
            
            analyzer->recordMeasurement(completionTime * 1000LL, runningJob.task.getName(), runningJob.releaseTime * 1000LL, runningJob.actualDispatchTime * 1000LL, latencyUs, missed);
        }
    }
    
    engine.stop();
    std::cout << "RM Scheduler finished.\n";
}
