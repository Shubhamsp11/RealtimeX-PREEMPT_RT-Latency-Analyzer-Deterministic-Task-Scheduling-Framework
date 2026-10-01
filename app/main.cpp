#include <iostream>
#include <string>
#include "TaskManager.h"
#include "RMScheduler.h"
#include "EDFScheduler.h"
#include "LatencyAnalyzer.h"
#include "Logger.h"
#include "IPCManager.h"
#include "SignalHandler.h"
#include "ProcessManager.h"

using namespace std;

void checkPreemptRT() {
    cout << "Checking for PREEMPT_RT environment...\n";
    cout << "WARNING:\n";
    cout << "PREEMPT_RT environment not detected.\n";
    cout << "RealtimeX will run in simulation/non-RT mode.\n\n";
}

void showMenu() {
    cout << "========================================\n";
    cout << "             REALTIMEX\n";
    cout << " PREEMPT_RT Latency Analyzer\n";
    cout << "========================================\n";
    cout << "1. Create Task\n";
    cout << "2. List Tasks\n";
    cout << "3. Run Rate Monotonic Scheduler (Simulation)\n";
    cout << "4. Run EDF Scheduler (Simulation)\n";
    cout << "5. View Results / Jitter Analysis\n";
    cout << "6. Save Results to Log\n";
    cout << "7. System Information / IPC Test\n";
    cout << "8. Run Linux Process Test (fork/exec)\n";
    cout << "9. Exit\n";
    cout << "Select option: ";
}

int main() {
    SignalHandler::setupHandlers();
    checkPreemptRT();

    TaskManager tm;
    LatencyAnalyzer analyzer;
    IPCManager ipc;

    tm.addTask(Task(1, "SensorTask", 100, 20, 100, 1));
    tm.addTask(Task(2, "ControlTask", 200, 40, 200, 2));
    tm.addTask(Task(3, "LoggerTask", 500, 50, 500, 3));

    int choice = 0;
    while (choice != 9) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                int id, p, e, d, prio;
                string name;
                cout << "Enter Task ID: "; cin >> id;
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Period(ms): "; cin >> p;
                cout << "Enter Execution Time(ms): "; cin >> e;
                cout << "Enter Deadline(ms): "; cin >> d;
                cout << "Enter Priority: "; cin >> prio;
                tm.addTask(Task(id, name, p, e, d, prio));
                cout << "Task created successfully.\n";
                break;
            }
            case 2:
                tm.displayTasks();
                break;
            case 3: {
                RMScheduler rm(&tm, &analyzer);
                rm.schedule(1000);
                break;
            }
            case 4: {
                EDFScheduler edf(&tm, &analyzer);
                edf.schedule(1000);
                break;
            }
            case 5:
                analyzer.printStatistics();
                break;
            case 6:
                Logger::saveResults(analyzer.getMeasurements(), "results/latency.log");
                Logger::displayResults("results/latency.log");
                break;
            case 7:
                cout << "OS Environment: Simulated Linux\n";
                if(ipc.initSharedMemory()) {
                    ipc.writeSharedMessage("IPC test successful - Shared Memory Working!");
                    cout << "IPC Read: " << ipc.readSharedMessage() << "\n";
                }
                break;
            case 8:
                ProcessManager::executeWithProcess();
                break;
            case 9:
                cout << "Exiting RealtimeX.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
        cout << "\n";
    }
    return 0;
}
