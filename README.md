# CPU Scheduling Algorithms

This repository contains C++ implementations of basic CPU scheduling algorithms specifically designed to work with **Turbo C++** for learning and reference purposes:

- **FCFS** – First Come, First Served
- **SJF** – Shortest Job First (non-preemptive)
- **SRTF** – Shortest Remaining Time First (preemptive)

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
