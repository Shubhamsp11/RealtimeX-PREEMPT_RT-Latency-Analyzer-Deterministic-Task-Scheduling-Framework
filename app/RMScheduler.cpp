#include "RMScheduler.h"
#include "TaskExecutionEngine.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

void RMScheduler::schedule(int durationMs) {
    std::cout << "\n--- Running Rate Monotonic Scheduler (" << durationMs << " ms) [SIMULATION MODE] ---\n";
    
    std::vector<Task> tasks = taskManager->getTasks();
    if (tasks.empty()) {
        std::cout << "No tasks to schedule.\n";
        return;
    }

    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.getPeriod() < b.getPeriod();
    });

    TaskExecutionEngine engine;

    int currentTime = 0;
    while (currentTime < durationMs) {
        bool idle = true;
        for (auto& task : tasks) {
            if (currentTime % task.getPeriod() == 0) {
                idle = false;
                std::cout << "[" << currentTime << "ms] Dispatching RM Task: " << task.getName() << "\n";
                
                auto start = std::chrono::high_resolution_clock::now();
                
                // Dispatch to worker thread using condition_variable
                engine.executeTask(&task);
                
                // For accurate simulation tracking, we wait for execution time (could be replaced by wait on completion)
                std::this_thread::sleep_for(std::chrono::milliseconds(task.getExecutionTime()));
                
                auto end = std::chrono::high_resolution_clock::now();
                
                long long actualExecUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                long long expectedExecUs = task.getExecutionTime() * 1000LL;
                long long latency = actualExecUs - expectedExecUs;
                
                bool missedDeadline = (actualExecUs > task.getDeadline() * 1000LL);
                analyzer->recordMeasurement(task.getName(), expectedExecUs, actualExecUs, latency, missedDeadline);
                
                currentTime += task.getExecutionTime();
                break;
            }
        }
        if (idle) {
            currentTime += 1;
        }
    }
    
    engine.stop();
    std::cout << "RM Scheduler finished.\n";
}
