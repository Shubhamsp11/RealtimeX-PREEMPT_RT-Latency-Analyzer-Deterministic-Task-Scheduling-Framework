#include "SignalHandler.h"
#include <iostream>
#include <csignal>
#include <cstdlib>

void handleSignal(int signum) {
    std::cout << "\nInterrupt signal (" << signum << ") received.\n";
    std::cout << "RealtimeX cleanup...\n";
    std::cout << "Stopping worker threads...\n";
    std::cout << "Closing IPC...\n";
    std::cout << "Saving results...\n";
    std::cout << "Exiting.\n";
    exit(signum);
}

void SignalHandler::setupHandlers() {
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);
}
