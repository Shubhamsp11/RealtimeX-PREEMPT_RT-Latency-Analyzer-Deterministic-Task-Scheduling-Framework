#ifndef LOGGER_H
#define LOGGER_H

#include "LatencyAnalyzer.h"
#include <string>

class Logger {
public:
    static void saveResults(const std::vector<Measurement>& measurements, const std::string& filename);
    static void displayResults(const std::string& filename);
};

#endif
