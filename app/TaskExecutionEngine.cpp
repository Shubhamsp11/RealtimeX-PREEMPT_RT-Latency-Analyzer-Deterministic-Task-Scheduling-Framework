#include "TaskExecutionEngine.h"
#include <iostream>
#include <chrono>

TaskExecutionEngine::TaskExecutionEngine() : running(true) {
    workerThread = std::thread(&TaskExecutionEngine::workerLoop, this);
}

TaskExecutionEngine::~TaskExecutionEngine() {
    stop();
}

void TaskExecutionEngine::executeTask(Task* task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        taskQueue.push(task);
    }
    cv.notify_one();
}

void TaskExecutionEngine::workerLoop() {
    while (running) {
        Task* currentTask = nullptr;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return !taskQueue.empty() || !running; });
            
            if (!running && taskQueue.empty()) {
                return;
            }

            currentTask = taskQueue.front();
            taskQueue.pop();
        }

        if (currentTask) {
            // Simulate execution
            std::this_thread::sleep_for(std::chrono::milliseconds(currentTask->getExecutionTime()));
        }
    }
}

void TaskExecutionEngine::stop() {
    running = false;
    cv.notify_all();
    if (workerThread.joinable()) {
        workerThread.join();
    }
}
