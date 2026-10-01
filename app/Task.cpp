#include "Task.h"

Task::Task(int id, const std::string& name, int period, int executionTime, int deadline, int priority)
    : id(id), name(name), period(period), executionTime(executionTime), deadline(deadline), priority(priority), status(TaskStatus::READY) {}

int Task::getId() const { return id; }
std::string Task::getName() const { return name; }
int Task::getPeriod() const { return period; }
int Task::getExecutionTime() const { return executionTime; }
int Task::getDeadline() const { return deadline; }
int Task::getPriority() const { return priority; }
TaskStatus Task::getStatus() const { return status; }

void Task::setStatus(TaskStatus s) { status = s; }
void Task::setPriority(int p) { priority = p; }
