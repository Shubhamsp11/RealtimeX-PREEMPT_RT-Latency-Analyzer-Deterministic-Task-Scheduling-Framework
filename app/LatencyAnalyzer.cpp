#include "LatencyAnalyzer.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>

LatencyAnalyzer::LatencyAnalyzer() : currentSchedulerName("Unknown") {}

void LatencyAnalyzer::clear(const std::string& schedulerName) {
    std::lock_guard<std::mutex> lock(laMutex);
    measurements.clear();
    currentSchedulerName = schedulerName;
}

void LatencyAnalyzer::recordMeasurement(long long simulatedTimeUs, const std::string& taskName, long long expectedReleaseUs, long long actualDispatchUs, long long latencyUs, bool missedDeadline) {
    std::lock_guard<std::mutex> lock(laMutex);
    measurements.push_back({simulatedTimeUs, taskName, expectedReleaseUs, actualDispatchUs, latencyUs, missedDeadline});
}

void LatencyAnalyzer::printStatistics() {
    std::lock_guard<std::mutex> lock(laMutex);
    std::cout << "\n====================================\n";
    std::cout << "REALTIMEX RESULTS\n";
    std::cout << "Scheduler: " << currentSchedulerName << "\n";
    std::cout << "Mode: SIMULATION\n";
    std::cout << "====================================\n";
    
    if (measurements.empty()) {
        std::cout << "No measurements recorded for this run.\n";
        return;
    }

    std::map<std::string, std::vector<Measurement>> grouped;
    for (const auto& m : measurements) {
        grouped[m.taskName].push_back(m);
    }

    std::cout << "Total Tasks Run   : " << measurements.size() << "\n\n";

    std::cout << "Task Status\n";
    std::cout << "------------------------------------\n";
    for (const auto& pair : grouped) {
        bool anyMissed = false;
        for (const auto& m : pair.second) {
            if (m.missedDeadline) anyMissed = true;
        }
        std::cout << std::left << std::setw(15) << pair.first << " : " 
                  << (anyMissed ? "FAIL (Missed Deadline)" : "PASS") << "\n";
    }

    std::cout << "\nExecution Statistics\n";
    std::cout << "------------------------------------\n";
    for (const auto& pair : grouped) {
        const auto& name = pair.first;
        const auto& meas = pair.second;
        
        long long minLatency = meas[0].latencyUs;
        long long maxLatency = meas[0].latencyUs;
        long long totalLatency = 0;
        int missedCount = 0;

        for (const auto& m : meas) {
            if (m.latencyUs < minLatency) minLatency = m.latencyUs;
            if (m.latencyUs > maxLatency) maxLatency = m.latencyUs;
            totalLatency += m.latencyUs;
            if (m.missedDeadline) missedCount++;
        }

        long long avgLatency = totalLatency / meas.size();
        long long jitter = maxLatency - minLatency;

        std::cout << name << ":\n";
        std::cout << "  Executions      : " << meas.size() << "\n";
        std::cout << "  Average Latency : " << avgLatency << " us\n";
        std::cout << "  Maximum Latency : " << maxLatency << " us\n";
        std::cout << "  Minimum Latency : " << minLatency << " us\n";
        std::cout << "  Jitter          : " << jitter << " us\n";
        std::cout << "  Deadline Misses : " << missedCount << "\n\n";
    }
}

std::vector<Measurement> LatencyAnalyzer::getMeasurements() {
    std::lock_guard<std::mutex> lock(laMutex);
    return measurements;
}
