#ifndef LATENCYANALYZER_H
#define LATENCYANALYZER_H

#include <string>
#include <vector>
#include <mutex>

struct Measurement {
    long long simulatedTimeUs;
    std::string taskName;
    long long expectedReleaseUs;
    long long actualDispatchUs;
    long long latencyUs;
    bool missedDeadline;
};

class LatencyAnalyzer {
private:
    std::vector<Measurement> measurements;
    std::mutex laMutex;
    std::string currentSchedulerName;

public:
    LatencyAnalyzer();
    void clear(const std::string& schedulerName);
    void recordMeasurement(long long simulatedTimeUs, const std::string& taskName, long long expectedReleaseUs, long long actualDispatchUs, long long latencyUs, bool missedDeadline);
    void printStatistics();
    std::vector<Measurement> getMeasurements();
};

#endif
