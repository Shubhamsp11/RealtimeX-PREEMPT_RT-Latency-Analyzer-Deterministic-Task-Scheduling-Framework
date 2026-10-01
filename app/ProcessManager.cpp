#include "ProcessManager.h"
#include <iostream>

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#endif

void ProcessManager::executeWithProcess() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    std::cout << "[ProcessManager] Forking a new process...\n";
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!\n";
    } else if (pid == 0) {
        // Child process
        std::cout << "[Child Process] PID: " << getpid() << " Executing 'ls' command...\n";
        execlp("ls", "ls", "-l", nullptr);
        // If exec fails
        std::cerr << "Exec failed!\n";
        exit(1);
    } else {
        // Parent process
        std::cout << "[Parent Process] PID: " << getpid() << " waiting for child (PID: " << pid << ")...\n";
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            std::cout << "[Parent Process] Child exited with status " << WEXITSTATUS(status) << "\n";
        }
    }
#else
    std::cout << "[ProcessManager] Fork/Exec is only supported on Linux/Unix systems.\n";
#endif
}
