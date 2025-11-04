// BLOCK 1
#include <iostream.h>
#include <conio.h>
#include <string.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt, done;
};

void main() {
    clrscr();

    int n, i, j;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[20];

    for (i = 0; i < n; i++) {
        cout << "\nEnter Process ID: ";
        cin >> p[i].id;
        cout << "Enter Arrival Time: ";
        cin >> p[i].at;
        cout << "Enter Burst Time: ";
        cin >> p[i].bt;
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

    int t = 0, busy = 0, completed = 0;
    float avgtat = 0, avgwt = 0;

// BLOCK 2

    // Gantt chart tracking
    int ganttTime[100];
    int ganttCount = 0;
    char ganttLabel[100][10]; // store "P?" or "IDLE"

    while (completed < n) {
        int idx = -1;
        int min_bt = 9999;

        // Find the shortest job that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].done == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU is idle -> jump to next process arrival
            int nextArrival = 9999;
            for (i = 0; i < n; i++) {
                if (p[i].done == 0 && p[i].at < nextArrival)
                    nextArrival = p[i].at;
            }

            // Record idle in Gantt
            ganttTime[ganttCount] = t;
            strcpy(ganttLabel[ganttCount], "IDLE");
            ganttCount++;

            t = nextArrival; // Jump to next process arrival
            continue;
        }

        // Record process start time in Gantt
        ganttTime[ganttCount] = t;
        strcpy(ganttLabel[ganttCount], "");
        ganttLabel[ganttCount][0] = 'P';
        ganttLabel[ganttCount][1] = p[idx].id;
        ganttLabel[ganttCount][2] = '\0';
        ganttCount++;

        // Process executes
        p[idx].ct = t + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        t = p[idx].ct;
        busy += p[idx].bt;
        completed++;
    }

// BLOCK 3

    // Display results
    cout << "\n\nID\tAT\tBT\tCT\tTAT\tWT";
    cout << "\n-----------------------------------------\n";
    for (i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
        avgtat += p[i].tat;
        avgwt += p[i].wt;
    }

    int totalTime = 0;
    for (i = 0; i < n; i++) {
        if (p[i].ct > totalTime)
            totalTime = p[i].ct;
    }

    float cpu = (busy * 100.0) / totalTime;
    cout << "\nAVG TAT: " << avgtat / n;
    cout << "\nAVG WT: " << avgwt / n;
    cout << "\nCPU Util: " << cpu << "%";

// BLOCK 4

    // Gantt Chart
    cout << "\n\nGANTT CHART\n";
    for (i = 0; i < ganttCount; i++) {
        cout << "|  " << ganttLabel[i] << "  ";
    }
    cout << "|\n";

    for (i = 0; i < ganttCount; i++) {
        cout << ganttTime[i] << "\t";
    }
    cout << t;

    getch();
}
