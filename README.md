# OS Scheduling Algorithms - C++ Examples

This folder contains C++ implementations of various Operating System (OS) process scheduling algorithms, as well as a simple multithreading example. These programs are intended for educational purposes to help understand how different scheduling strategies work.

## Contents
- `Threading.cpp`: Demonstrates basic multithreading in C++ by running two tasks concurrently.
- `FCFS.cpp`: First-Come, First-Served scheduling algorithm.
- `SJF_NON_PREEMPTIVE.cpp`: Shortest Job First (Non-Preemptive) scheduling algorithm.
- `SJF_PREEMPTIVE.cpp`: Shortest Job First (Preemptive) scheduling algorithm.
- `PRIORITY_NON_PREEMPTIVE.cpp`: Priority Scheduling (Non-Preemptive).
- `PRIORITY_PREEMPTIVE.cpp`: Priority Scheduling (Preemptive).
- `Round_Robin.cpp`: Round Robin scheduling algorithm.
- `MLQ.cpp`: Multi-Level Queue scheduling algorithm.

## How to Use
Each file is a standalone C++ program. You can compile and run them individually to see how each scheduling algorithm works. Most programs will prompt for process information and display scheduling results, Gantt charts, and statistics.

## Compilation Instructions

### On Linux/macOS
Use the following command to compile any of the C++ files:
```
g++ -std=c++11 filename.cpp -o outputname
./outputname
```
Replace `filename.cpp` and `outputname` as needed.

### On Windows
- Some files (like `Threading.cpp`) use POSIX-specific functions (`sleep`, `unistd.h`). See below for Windows compatibility notes.
- For C++11 threading support, use MinGW-w64 or a modern compiler.
- Example compilation:
```
g++ -std=c++11 filename.cpp -o outputname.exe
outputname.exe
```

### Special Note for `Threading.cpp` on Windows
- Replace `#include <unistd.h>` and `sleep(1);` with:
  ```cpp
  #include <chrono>
  #include <thread>
  std::this_thread::sleep_for(std::chrono::seconds(1));
  ```
- If you see errors about `thread` or `this_thread`, your compiler may not support C++11 threads. Install MinGW-w64 or use a modern compiler.

## Troubleshooting
- If you see errors about missing headers or functions, check the code comments for platform-specific instructions.
- For threading, ensure your compiler supports C++11 or later.

## License
This code is for educational purposes. 