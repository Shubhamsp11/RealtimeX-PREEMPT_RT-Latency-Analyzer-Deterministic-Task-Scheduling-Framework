#include "EDFScheduler.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

struct Job {
    Task task;
    int releaseTime;
    int absoluteDeadline;
    int remainingTime;
};

void EDFScheduler::schedule(int durationMs) {
    std::cout << "\n--- Running Earliest Deadline First Scheduler (" << durationMs << " ms) [SIMULATION MODE] ---\n";
    
    std::vector<Task> tasks = taskManager->getTasks();
    if (tasks.empty()) {
        std::cout << "No tasks to schedule.\n";
        return;
    }

    std::vector<Job> activeJobs;
    int currentTime = 0;

    while (currentTime < durationMs) {
        for (const auto& task : tasks) {
            if (currentTime % task.getPeriod() == 0) {
                Job newJob = {task, currentTime, currentTime + task.getDeadline(), task.getExecutionTime()};
                activeJobs.push_back(newJob);
            }
        }

        if (activeJobs.empty()) {
            currentTime++;
            continue;
        }

        std::sort(activeJobs.begin(), activeJobs.end(), [](const Job& a, const Job& b) {
            return a.absoluteDeadline < b.absoluteDeadline;
        });

        Job& currentJob = activeJobs.front();
        std::cout << "[" << currentTime << "ms] Executing EDF Task: " << currentJob.task.getName() << " (Deadline: " << currentJob.absoluteDeadline << ")\n";
        
        auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(currentJob.remainingTime));
        auto end = std::chrono::high_resolution_clock::now();
        
        long long actualExecUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        long long expectedExecUs = currentJob.remainingTime * 1000LL;
        long long latency = actualExecUs - expectedExecUs;
        
        bool missedDeadline = (currentTime + currentJob.remainingTime) > currentJob.absoluteDeadline;
        analyzer->recordMeasurement(currentJob.task.getName(), expectedExecUs, actualExecUs, latency, missedDeadline);

        currentTime += currentJob.remainingTime;
        activeJobs.erase(activeJobs.begin());
    }
    std::cout << "EDF Scheduler finished.\n";
}
