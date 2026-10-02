#include "EDFScheduler.h"
#include "IPCManager.h"
#include "LatencyAnalyzer.h"
#include "Logger.h"
#include "ProcessManager.h"
#include "RMScheduler.h"
#include "SignalHandler.h"
#include "TaskManager.h"
#include <iostream>
#include <string>

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/utsname.h>
#endif

using namespace std;

#include <cstdio>
#include <cstring>

bool isPreemptRTEnabled() {
  bool is_rt = false;
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  FILE* pipe = popen("zcat /proc/config.gz 2>/dev/null", "r");
  if (pipe) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
      if (strstr(buffer, "CONFIG_PREEMPT_RT=y") != nullptr) {
        is_rt = true;
        break;
      }
    }
    pclose(pipe);
  }
#endif
  return is_rt;
}

void checkPreemptRT() {
  cout << "Checking for PREEMPT_RT environment...\n";
  if (isPreemptRTEnabled()) {
    cout << "PREEMPT_RT environment detected.\n";
    cout << "RealtimeX will run with PREEMPT_RT enabled.\n\n";
  } else {
    cout << "WARNING:\n";
    cout << "PREEMPT_RT environment not detected.\n";
    cout << "RealtimeX will run in simulation/non-RT mode.\n\n";
  }
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
      cout << "Enter Task ID: ";
      cin >> id;
      cout << "Enter Name: ";
      cin >> name;
      cout << "Enter Period(ms): ";
      cin >> p;
      cout << "Enter Execution Time(ms): ";
      cin >> e;
      cout << "Enter Deadline(ms): ";
      cin >> d;
      cout << "Enter Priority: ";
      cin >> prio;
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
    case 7: {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
      struct utsname buffer;
      if (uname(&buffer) == 0) {
        cout << "OS Environment: " << buffer.sysname << " / WSL\n";
        cout << "Kernel: " << buffer.release << " (" << buffer.version << ")\n";
      } else {
        cout << "OS Environment: Linux (uname failed)\n";
      }
#else
      cout << "OS Environment: Windows (Native) / Unknown\n";
#endif
      if (isPreemptRTEnabled()) {
        cout << "PREEMPT_RT: DETECTED\n";
      } else {
        cout << "PREEMPT_RT: NOT DETECTED\n";
      }
      if (ipc.initSharedMemory()) {
        ipc.writeSharedMessage("IPC test successful - Shared Memory Working!");
        cout << "IPC Read: " << ipc.readSharedMessage() << "\n";
      }
      break;
    }
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
