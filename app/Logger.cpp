#include "Logger.h"
#include <fstream>
#include <iostream>

void Logger::saveResults(const std::vector<Measurement>& measurements, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error opening file " << filename << " for writing.\n";
        return;
    }
    
    outFile << "SimulatedTimeUs,TaskName,ExpectedReleaseUs,ActualDispatchUs,LatencyUs,MissedDeadline\n";
    for (const auto& m : measurements) {
        outFile << m.simulatedTimeUs << ","
                << m.taskName << ","
                << m.expectedReleaseUs << ","
                << m.actualDispatchUs << ","
                << m.latencyUs << ","
                << (m.missedDeadline ? "1" : "0") << "\n";
    }
    outFile.close();
    std::cout << "Results saved to " << filename << "\n";
}

void Logger::displayResults(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file " << filename << " for reading.\n";
        return;
    }
    
    std::string line;
    std::cout << "\n--- Results from " << filename << " ---\n";
    while (std::getline(inFile, line)) {
        std::cout << line << "\n";
    }
    inFile.close();
}
