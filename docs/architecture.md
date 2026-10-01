# Architecture

RealtimeX follows a modular, user-space deterministic scheduling framework.

```text
                    RealtimeX
                       |
        +--------------+--------------+
        |              |              |
        v              v              v
   Task Manager   Scheduler       Latency Analyzer
        |              |              |
        +--------------+--------------+
                       |
                       v
                Task Execution Engine
```

### Components
1. **TaskManager**: Manages STL containers of tasks.
2. **Scheduler**: Abstract base class. Subclassed by RMScheduler and EDFScheduler.
3. **LatencyAnalyzer**: Records expected vs actual execution times.
4. **IPCManager**: Demonstrates SysV Shared memory.
5. **Logger**: Writes latency metrics to CSV style logs.
6. **Kernel Module**: Exposes a `/dev/realtimex` char device and runs kernel timers.
