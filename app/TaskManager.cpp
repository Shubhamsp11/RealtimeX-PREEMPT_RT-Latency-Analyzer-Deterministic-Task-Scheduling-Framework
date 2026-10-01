#include "TaskManager.h"
#include <iostream>
#include <iomanip>

void TaskManager::addTask(const Task& task) {
    std::lock_guard<std::mutex> lock(tmMutex);
    tasks.push_back(task);
    taskMap[task.getId()] = task;
}

std::vector<Task> TaskManager::getTasks() {
    std::lock_guard<std::mutex> lock(tmMutex);
    return tasks;
}

void TaskManager::displayTasks() {
    std::lock_guard<std::mutex> lock(tmMutex);
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(15) << "NAME" 
              << std::setw(10) << "PERIOD" 
              << std::setw(10) << "DEADLINE" 
              << std::setw(15) << "STATUS" << "\n";
    std::cout << "------------------------------------------------------\n";
    for (const auto& task : tasks) {
        std::string statusStr = "";
        switch (task.getStatus()) {
            case TaskStatus::READY: statusStr = "READY"; break;
            case TaskStatus::RUNNING: statusStr = "RUNNING"; break;
            case TaskStatus::COMPLETED: statusStr = "COMPLETED"; break;
            case TaskStatus::MISSED_DEADLINE: statusStr = "MISSED"; break;
        }
        std::cout << std::left << std::setw(5) << task.getId() 
                  << std::setw(15) << task.getName() 
                  << std::to_string(task.getPeriod()) + "ms" << std::setw(6) << ""
                  << std::to_string(task.getDeadline()) + "ms" << std::setw(4) << ""
                  << std::setw(15) << statusStr << "\n";
    }
}

Task* TaskManager::getTaskById(int id) {
    std::lock_guard<std::mutex> lock(tmMutex);
    if (taskMap.find(id) != taskMap.end()) {
        return &taskMap[id];
    }
    return nullptr;
}
