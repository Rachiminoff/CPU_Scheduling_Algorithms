// BLOCK 1
#include <iostream.h>
#include <conio.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt, rt, done, pr;
};

void main() {
    clrscr();

    int n, i, j;
    cout << "Enter number of processes: ";
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
        cout << "Priority (lower = higher priority): ";
        cin >> p[i].pr;

        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    // Sort by arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
// BLOCK 2
    int t = 0, completed = 0, busy = 0;
    float avgtat = 0, avgwt = 0;
    int ganttOrder[500], ganttTime[500];
    int ganttCount = 0;

    int prev = -2;  // previous running process for detecting context switch

    while (completed < n) {

        int idx = -1;
        int best_pr = 9999;

        // Select highest priority READY process (lowest priority number)
        for (i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].done == 0 && p[i].rt > 0) {
                if (p[i].pr < best_pr) {
                    best_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        // If no process is ready, CPU is IDLE
        if (idx == -1) {

            // Record IDLE only when switching into idle state
            if (prev != -1) {
                ganttOrder[ganttCount] = -1;  // -1 means IDLE
                ganttTime[ganttCount] = t;
                ganttCount++;
                prev = -1;
            }

            t++;   // move time forward
            continue;
        }

        // Context switch tracking (process change recorded)
        if (prev != idx) {
            ganttOrder[ganttCount] = idx;
            ganttTime[ganttCount] = t;
            ganttCount++;
            prev = idx;
        }

        // Execute for 1 time unit
        p[idx].rt--;
        t++;
        busy++;          

        // Process completed
        if (p[idx].rt == 0) {
            p[idx].done = 1;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }
// BLOCK 3
    cout << "\n\nID\tAT\tBT\tP\tCT\tTAT\tWT";
    cout << "\n-------------------------------------------------------\n";
    for (i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].pr << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";

        avgtat += p[i].tat;
        avgwt += p[i].wt;
    }

    int totalTime = t;
    float cpu = (busy * 100.0) / totalTime;

    cout << "\nAVG TAT: " << avgtat / n;
    cout << "\nAVG WT : " << avgwt / n;
    cout << "\nCPU Util: " << cpu << "%";

// BLOCK 4
    cout << "\n\nGANTT CHART\n";

    // process labels
    for (i = 0; i < ganttCount; i++) {
        if (ganttOrder[i] == -1)
            cout << "|  IDLE  ";
        else
            cout << "|  P" << p[ganttOrder[i]].id << "  ";
    }
    cout << "|\n";

    // time markers
    for (i = 0; i < ganttCount; i++) {
        cout << ganttTime[i] << "\t";
    }
    cout << t;

    getch();
}
