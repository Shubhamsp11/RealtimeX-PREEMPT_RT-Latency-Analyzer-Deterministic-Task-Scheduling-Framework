#ifndef TASK_H
#define TASK_H

#include <string>

enum class TaskStatus { READY, RUNNING, COMPLETED, MISSED_DEADLINE };

class Task {
private:
    int id;
    std::string name;
    int period;
    int executionTime;
    int deadline;
    int priority;
    TaskStatus status;

public:
    Task(int id, const std::string& name, int period, int executionTime, int deadline, int priority);
    
    int getId() const;
    std::string getName() const;
    int getPeriod() const;
    int getExecutionTime() const;
    int getDeadline() const;
    int getPriority() const;
    TaskStatus getStatus() const;
    
    void setStatus(TaskStatus s);
    void setPriority(int p);
};

#endif
