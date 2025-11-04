# CPU Scheduling Algorithms

This repository contains C++ implementations of basic CPU scheduling algorithms specifically designed to work with **Turbo C++** for learning and reference purposes:

- **FCFS** – First Come, First Served
- **SJF** – Shortest Job First (non-preemptive)
- **SRTF** – Shortest Remaining Time First (preemptive)

### Idle Logic Versions

In addition to the standard implementations, **separate files** are included that feature **idle time handling**, ensuring the CPU waits (stays idle) when no process is ready to execute.

- `FCFS_idle.cpp` – FCFS with CPU idle handling  
- `SJF_idle.cpp` – SJF with CPU idle handling  
- `SRTF_idle.cpp` – SRTF with CPU idle handling  

These versions simulate **realistic CPU scheduling**, where the CPU remains idle if no process has arrived yet.  

They are kept **as separate files** to clearly distinguish between:
- **Basic versions** - focus purely on algorithm logic. Idle time is reflected **only as a gap in the timeline**, not explicitly shown in the Gantt chart.  
- **Idle versions** - explicitly show **CPU idle periods** in the Gantt chart, making the execution timeline more realistic.  

This separation helps learners understand the **core scheduling logic** first, before studying the **extended behavior** with idle handling.

### Template File

A **skeleton template** is also provided for creating new CPU scheduling algorithms:

- `Template_CPU_Scheduling.cpp`

This file contains only the **basic structure** (input, logic, output, and Gantt chart blocks) without any specific algorithm logic — ideal for experimentation or building new schedulers.  

Each algorithm follows the same general structure, divided into **four blocks**:

1. **Block 1 – Input Section:** Collect process data from the user.  
2. **Block 2 – Main Logic:** Compute completion, turnaround, and waiting times. This is the block that changes the most between algorithms.  
3. **Block 3 – Output Section:** Display results in a table with all relevant times.  
4. **Block 4 – Gantt Chart:** Visualize the execution order of processes.

> Note: The block-based division is intended for educational purposes, in order to better help understand which parts of the code are common and which parts are algorithm-specific.

> The code uses Turbo C++ conventions like `clrscr()` and `getch()`. Minor modifications may be required to run in modern compilers.

## How to Run

1. Open the project in Turbo C++.
2. Compile and run the program.
3. Input the number of processes and their details when prompted.

## Notes for Modern Compilers

- Functions like `clrscr()` and `getch()` may need to be replaced with alternatives such as `system("cls")` or standard input handling.
- `iostream.h` can be replaced with `#include <iostream>` and `using namespace std;`.
- The logic itself works universally; only minor syntax adjustments are required.

## Quick Algorithm Summary

- **FCFS:** Run processes in order of arrival, no preemption.  
- **SJF:** Pick the process with the shortest burst time among ready processes.  
- **SRTF:** Pick the process with the shortest remaining time at each moment; preempt if a shorter process arrives.

## Purpose

The codes are intended for educational use and as an archive for study/reference.
