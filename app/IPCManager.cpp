#include "IPCManager.h"
#include <iostream>
#include <cstring>

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/ipc.h>
#include <sys/shm.h>
#define HAS_SYS_SHM
#endif

IPCManager::IPCManager() : shmId(-1), shmPtr(nullptr) {}

IPCManager::~IPCManager() {
    cleanup();
}

bool IPCManager::initSharedMemory() {
#ifdef HAS_SYS_SHM
    key_t key = 1234;
    shmId = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmId < 0) {
        std::cerr << "shmget failed\n";
        return false;
    }
    shmPtr = shmat(shmId, nullptr, 0);
    if (shmPtr == (void*)-1) {
        std::cerr << "shmat failed\n";
        return false;
    }
    return true;
#else
    std::cerr << "[IPC] Shared Memory not supported on this OS (Linux required).\n";
    return false;
#endif
}

bool IPCManager::writeSharedMessage(const std::string& msg) {
#ifdef HAS_SYS_SHM
    if (shmPtr) {
        std::strncpy((char*)shmPtr, msg.c_str(), 1024);
        return true;
    }
#endif
    return false;
}

std::string IPCManager::readSharedMessage() {
#ifdef HAS_SYS_SHM
    if (shmPtr) {
        return std::string((char*)shmPtr);
    }
#endif
    return "";
}

void IPCManager::cleanup() {
#ifdef HAS_SYS_SHM
    if (shmPtr) {
        shmdt(shmPtr);
        shmPtr = nullptr;
    }
    if (shmId >= 0) {
        shmctl(shmId, IPC_RMID, nullptr);
        shmId = -1;
    }
#endif
}
