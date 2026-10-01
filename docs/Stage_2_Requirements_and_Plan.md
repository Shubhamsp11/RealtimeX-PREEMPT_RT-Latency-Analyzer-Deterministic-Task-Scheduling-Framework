# Stage 2 – Project Requirements & Development Plan

## 1. Functional Requirements

| ID | Requirement |
|---|---|
| FR1 | Create a task with ID, name, period, execution time, deadline, and priority. |
| FR2 | List the configured tasks. |
| FR3 | Simulate Rate Monotonic scheduling. |
| FR4 | Simulate EDF scheduling. |
| FR5 | Calculate/display latency, jitter, execution count, and deadline misses. |
| FR6 | Save scheduling results to a log file. |
| FR7 | Display system information and test shared-memory IPC. |
| FR8 | Demonstrate Linux fork/exec process handling. |
| FR9 | Exit the application cleanly. |

## 2. Non-Functional Requirements

- The implementation remains C/C++.
- The application should build using the existing Makefile.
- The program should run in Linux/WSL.
- Scheduling results should be clear and repeatable for the same simulation inputs.
- The program should report when PREEMPT_RT is not detected instead of claiming real-time kernel execution.

## 3. Main Modules

1. **Task Management** – stores and displays task parameters.
2. **RM Scheduler** – performs Rate Monotonic simulation.
3. **EDF Scheduler** – performs Earliest Deadline First simulation.
4. **Latency/Jitter Analysis** – calculates timing statistics.
5. **Result Logging** – saves results to `results/latency.log`.
6. **System/IPC Tests** – checks Linux environment and shared memory.
7. **Process Test** – demonstrates `fork()` and `exec()`.

## 4. Development Plan

| Stage | Work |
|---|---|
| 1 | Define project idea, problem, scope, and expected outcome. |
| 2 | Define requirements and modules. |
| 3 | Design architecture and data flow. |
| 4 | Implement and integrate the core C/C++ modules. |
| 5 | Test every menu function and fix issues. |
| 6 | Prepare final demonstration, results, limitations, and report. |

## 5. Deliverables

Minimum deliverables:
- working C/C++ source code
- Makefile
- tested executable
- result log
- simple project documentation
- architecture/design diagrams
- testing results
