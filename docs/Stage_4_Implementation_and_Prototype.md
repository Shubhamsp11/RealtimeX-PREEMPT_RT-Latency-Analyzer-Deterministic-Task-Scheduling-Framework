# Stage 4 – Initial Implementation & Prototype

## 1. Implementation

The working prototype was implemented as a C/C++ command-line application.

The main menu provides nine operations:

1. Create Task
2. List Tasks
3. Run Rate Monotonic Scheduler
4. Run EDF Scheduler
5. View Results / Jitter Analysis
6. Save Results to Log
7. System Information / IPC Test
8. Linux Process Test
9. Exit

## 2. Initial Task Set

The working demonstration uses:

| Task | Period | Execution Time | Deadline | Priority |
|---|---:|---:|---:|---:|
| SensorTask | 100 ms | 20 ms | 100 ms | 1 |
| ControlTask | 200 ms | 40 ms | 200 ms | 2 |
| LoggerTask | 500 ms | 50 ms | 500 ms | 3 |

## 3. Example Task Listing

```text
ID   NAME           PERIOD    DEADLINE  STATUS
------------------------------------------------------
1    SensorTask     100ms      100ms    READY
2    ControlTask    200ms      200ms    READY
3    LoggerTask     500ms      500ms    READY
```

## 4. RM Prototype Output

Example scheduling events:

```text
[0ms] SensorTask
Release: 0ms
Dispatch: 0ms
Latency: 0ms
Deadline: 100ms

[20ms] ControlTask
Release: 0ms
Dispatch: 20ms
Latency: 20ms
Deadline: 200ms

[60ms] LoggerTask
Release: 0ms
Dispatch: 60ms
Latency: 60ms
Deadline: 500ms
```

The simulation then continues with later task releases.

## 5. EDF Prototype Output

The current task set also produces the same visible order for RM and EDF because the configured deadlines equal the periods.

Example:

```text
[0ms] SensorTask
[20ms] ControlTask
[60ms] LoggerTask
[100ms] SensorTask
[200ms] SensorTask
[220ms] ControlTask
```

This is a property of the current task set and does not by itself mean that RM and EDF are identical algorithms.

## 6. Implementation Status

The prototype successfully demonstrated:
- task creation/listing
- scheduling simulation
- timing analysis
- result logging
- system/IPC testing
- Linux process testing
