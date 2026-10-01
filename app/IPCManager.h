#ifndef IPCMANAGER_H
#define IPCMANAGER_H

#include <string>

class IPCManager {
public:
    IPCManager();
    ~IPCManager();

    bool initSharedMemory();
    bool writeSharedMessage(const std::string& msg);
    std::string readSharedMessage();
    void cleanup();

private:
    int shmId;
    void* shmPtr;
};

#endif
