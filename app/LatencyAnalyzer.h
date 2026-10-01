#ifndef LATENCYANALYZER_H
#define LATENCYANALYZER_H

#include <string>
#include <vector>
#include <mutex>

struct Measurement {
    std::string taskName;
    long long expectedTimeUs;
    long long actualTimeUs;
    long long latencyUs;
    bool missedDeadline;
};

class LatencyAnalyzer {
private:
    std::vector<Measurement> measurements;
    std::mutex laMutex;

public:
    void recordMeasurement(const std::string& taskName, long long expectedTime, long long actualTime, long long latency, bool missedDeadline);
    void printStatistics();
    std::vector<Measurement> getMeasurements();
};

#endif
