#ifndef TASKEXECUTIONENGINE_H
#define TASKEXECUTIONENGINE_H

#include "Task.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

class TaskExecutionEngine {
private:
    std::queue<Task*> taskQueue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread workerThread;
    std::atomic<bool> running;

    void workerLoop();

public:
    TaskExecutionEngine();
    ~TaskExecutionEngine();

    void executeTask(Task* task);
    void stop();
};

#endif
