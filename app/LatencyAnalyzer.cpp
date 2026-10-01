#include "LatencyAnalyzer.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void LatencyAnalyzer::recordMeasurement(const std::string& taskName, long long expectedTime, long long actualTime, long long latency, bool missedDeadline) {
    std::lock_guard<std::mutex> lock(laMutex);
    measurements.push_back({taskName, expectedTime, actualTime, latency, missedDeadline});
}

void LatencyAnalyzer::printStatistics() {
    std::lock_guard<std::mutex> lock(laMutex);
    if (measurements.empty()) {
        std::cout << "No measurements recorded.\n";
        return;
    }

    long long minLatency = measurements[0].latencyUs;
    long long maxLatency = measurements[0].latencyUs;
    long long totalLatency = 0;
    int missedCount = 0;

    for (const auto& m : measurements) {
        if (m.latencyUs < minLatency) minLatency = m.latencyUs;
        if (m.latencyUs > maxLatency) maxLatency = m.latencyUs;
        totalLatency += m.latencyUs;
        if (m.missedDeadline) missedCount++;
    }

    long long avgLatency = totalLatency / measurements.size();
    long long jitter = maxLatency - minLatency;

    std::cout << "\n====================================\n";
    std::cout << "REALTIMEX RESULTS\n";
    std::cout << "====================================\n";
    std::cout << "Total Tasks Run   : " << measurements.size() << "\n";
    std::cout << "Average Latency   : " << avgLatency << " us\n";
    std::cout << "Maximum Latency   : " << maxLatency << " us\n";
    std::cout << "Minimum Latency   : " << minLatency << " us\n";
    std::cout << "Jitter            : " << jitter << " us\n";
    std::cout << "Deadline Misses   : " << missedCount << "\n";
    std::cout << "\nTask Status\n";
    std::cout << "------------------------------------\n";
    for (const auto& m : measurements) {
        std::cout << std::left << std::setw(15) << m.taskName << " : " 
                  << (m.missedDeadline ? "FAIL (Missed Deadline)" : "PASS") << "\n";
    }
}

std::vector<Measurement> LatencyAnalyzer::getMeasurements() {
    std::lock_guard<std::mutex> lock(laMutex);
    return measurements;
}
