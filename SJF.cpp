//block 1
#include <iostream.h>
#include <conio.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt;
    int done; // B1-1 NEW SJF LOGIC flag for process completion
}; 

void main() {
    clrscr();

    int n, i, j;
    cout << "Number of processes: ";
    cin >> n;

    Process p[20];

    // Input
    for (i = 0; i < n; i++) {
        cout << "\nEnter Process ID: ";
        cin >> p[i].id;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time: ";
        cin >> p[i].bt;
        p[i].done = 0; //B1-2 NEW SJF LOGIC - initialize as not done
    } 

    // Sort by Arrival Time (bubble sort)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

//block 2
    // --- NEW SJF LOGIC START ---
    int t = 0, busy = 0, completed = 0;
    float avgtat = 0, avgwt = 0;

    int ganttOrder[20], ganttTime[20];
    int ganttCount = 0;

    while (completed < n) {
        int idx = -1; //idx = index
        int min_bt = 9999;  // placeholder large number to find the smallest BT during comparison

        // Loop through all processes to find the one with the smallest burst time that has already arrived and isn’t done yet
        // Among the remaining processes, find the one with the smallest burst time.
        // Store its position (index) so we can execute it next. Keep looping until all processes are finished
        for (i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].done == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        // If no process has arrived yet at the current time (t), the CPU does nothing (idle)
        // so move time forward by 1 until a process arrives
        if (idx == -1) {
            t++;
            continue;
        }

        ganttOrder[ganttCount] = idx;  // which process ran
        ganttTime[ganttCount] = t;     // when it started
        ganttCount++;                  // count that event

        // run calculations for the selected process
        p[idx].ct = t + p[idx].bt;     // time the process took to finish
        p[idx].tat = p[idx].ct - p[idx].at;  // turnaround time = time from arrival to finish
        p[idx].wt  = p[idx].tat - p[idx].bt; 
        p[idx].done = 1;               // mark this process as completed

        t = p[idx].ct;                 // move current time to when process finishes
        busy += p[idx].bt;             // add to total busy time
        completed++;                   // count this process as done
    }
    // --- NEW SJF LOGIC END ---

//block 3
    // Display Table
    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "----------------------------------------\n";
    for (i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";

        avgtat += p[i].tat;
        avgwt  += p[i].wt;
    }

    // --- NEW SJF LOGIC START ---
    // Loop through all processes to find the one with the largest CT
    // that's the total time the CPU was running.
    int totalTime = 0;
    for (i = 0; i < n; i++) {
        if (p[i].ct > totalTime)
            totalTime = p[i].ct;
    }

    float cpuUtilization = (busy * 100.0) / totalTime;
    // --- NEW SJF LOGIC END ---

    cout << "\nAverage Turnaround Time: " << avgtat / n;
    cout << "\nAverage Waiting Time   : " << avgwt / n;
    cout << "\nCPU Utilization        : " << cpuUtilization << "%\n";

//block 4
    // --- NEW SJF LOGIC ---
    cout << "\nGantt Chart:\n";

    if (ganttTime[0] != 0)
        cout << "|      ";  

    // Process bars
    for (i = 0; i < ganttCount; i++) {
        cout << "|  P" << p[ganttOrder[i]].id << "  "; // Get the ID of the process shown 
                                                       // at this position in the Gantt chart
    }
    cout << "|\n";

    // Timeline
    // If the first process didn’t start at 0, display 0 manually for clarity. purely cosmetic

    if (ganttTime[0] != 0)
        cout << "0\t";

    for (i = 0; i < ganttCount; i++) {
        cout << ganttTime[i] << "\t";
    }
    cout << t << "\n";

    getch();
}
