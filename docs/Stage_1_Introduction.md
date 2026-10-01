# Stage 1 – Project Introduction

## 1. Project Idea

RealtimeX is a C/C++ real-time scheduling simulation and latency analysis framework.

The project allows periodic tasks to be created and then simulated using:
- Rate Monotonic (RM) scheduling
- Earliest Deadline First (EDF) scheduling

The system records scheduling timing information and analyzes:
- latency
- jitter
- deadline misses

It also includes Linux/WSL system, IPC, and process-management tests.

## 2. Problem

Real-time systems must execute important tasks within predictable timing limits. A task may have a period, execution time, and deadline. If the task is delayed too much, its timing requirement may not be satisfied.

The project provides a simple way to observe and analyze this scheduling behavior without requiring a real PREEMPT_RT kernel.

## 3. Scope

The project covers:
- task creation and management
- RM scheduling simulation
- EDF scheduling simulation
- latency and jitter analysis
- deadline checking
- result logging
- PREEMPT_RT environment detection
- shared-memory IPC testing
- Linux fork/exec testing

## 4. Expected Outcome

The expected outcome is a working C/C++ application that can:
1. create and display real-time tasks;
2. simulate RM and EDF scheduling;
3. calculate scheduling latency and jitter;
4. identify deadline misses;
5. save results to a log;
6. demonstrate selected Linux system concepts.

## 5. Application

The project is useful for learning and demonstrating real-time scheduling concepts used in areas such as embedded systems, robotics, industrial control, automotive systems, and other systems where predictable task timing is important.
