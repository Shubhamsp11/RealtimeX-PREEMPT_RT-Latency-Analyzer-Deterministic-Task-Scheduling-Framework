#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>

class TaskManager {
private:
    std::vector<Task> tasks;
    std::map<int, Task> taskMap;
    std::mutex tmMutex;

public:
    void addTask(const Task& task);
    std::vector<Task> getTasks();
    void displayTasks();
    Task* getTaskById(int id);
};

#endif
