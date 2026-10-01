# Stage 3 – System Design & Architecture

## 1. Simple Architecture

```text
+----------------------+
|   RealtimeX CLI      |
|      Main Menu       |
+----------+-----------+
           |
     +-----+-------------------------------+
     |                                     |
     v                                     v
+------------+                    +------------------+
| Task       |                    | System / Linux   |
| Management |                    | Tests            |
+-----+------+                    +------------------+
      |
      v
+-----+------------------------------+
| Scheduling Simulation              |
|                                    |
|  Rate Monotonic   |   EDF          |
+---------+----------------+---------+
          |
          v
+---------------------------+
| Timing Analysis           |
| Latency / Jitter /        |
| Deadline Misses           |
+-------------+-------------+
              |
              v
+---------------------------+
| Results / latency.log     |
+---------------------------+
```

## 2. Main Responsibilities

### Task Management
Stores task parameters:
- task ID
- name
- period
- execution time
- deadline
- priority

### RM Scheduler
Selects tasks according to Rate Monotonic priority. Shorter-period tasks receive higher priority in the RM model.

### EDF Scheduler
Selects tasks according to the earliest deadline in the EDF model.

### Timing Analysis
Uses release and dispatch times to determine scheduling latency and related statistics.

### Result Logging
Stores scheduling records in the results log.

### Linux Tests
Checks the environment, shared-memory IPC, and process creation/management.

## 3. Simple Data Flow

```text
Create Task
    |
    v
Task Parameters
    |
    v
RM / EDF Simulation
    |
    v
Release + Dispatch Events
    |
    v
Latency / Jitter / Deadline Analysis
    |
    v
Display + Log Results
```

## 4. Simple Sequence

```text
User
 |
 | Create tasks
 v
RealtimeX
 |
 | Run RM/EDF
 v
Scheduler
 |
 | Generate dispatch events
 v
Analyzer
 |
 | Calculate latency/jitter/deadlines
 v
User
 |
 | Save results
 v
latency.log
```


