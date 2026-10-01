# RealtimeX
## PREEMPT_RT Latency Analyzer & Deterministic Task Scheduling Framework

A C++/Linux framework designed to demonstrate advanced system programming, process scheduling, and kernel module concepts.

### Concepts Demonstrated
- Linux System Programming (POSIX APIs, signals, IPC shared memory)
- C++17 (Multithreading, OOP, STL, Exception handling)
- Process & Task Scheduling (Rate Monotonic, Earliest Deadline First)
- Linux Kernel Module (LKM, Kernel Timers, Char Device)
- Makefile & git integration

### Building and Running
```bash
# Clone the repository
git clone <url>
cd RealtimeX

# Compile the user-space application
make

# Run the app
make run

# Run with demo inputs
make test

# Compile the kernel module
sudo make kernel

# Insert the kernel module
sudo insmod kernel/realtime_module.ko

# Check kernel logs
dmesg | tail

# Remove the kernel module
sudo rmmod realtime_module
```
