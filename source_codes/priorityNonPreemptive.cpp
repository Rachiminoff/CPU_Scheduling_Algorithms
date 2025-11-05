// BLOCK 1
#include <iostream.h>
#include <conio.h>
#include <string.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt, done;
    int prio; // NEW
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
        cout << "Enter Priority (lower number = higher priority): "; // NEW
    
        cin >> p[i].prio; // NEW
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

    int t = 0, busy = 0, completed = 0;
    float avgtat = 0, avgwt = 0;

    // Gantt chart tracking
    int ganttTime[100];
    int ganttCount = 0;
    char ganttLabel[100][10]; // store "P?" or "IDLE"

    while (completed < n) {
        int idx = -1;
        int min_prio = 9999;

        // Find process with highest priority that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].done == 0) {
                if (p[i].prio < min_prio) {
                    min_prio = p[i].prio;
                    idx = i;
                }
                // NEW: If priorities are equal, choose the earlier arrival
                else if (p[i].prio == min_prio && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU idle → skip to next arrival
            int nextArrival = 9999;
            for (i = 0; i < n; i++) {
                if (p[i].done == 0 && p[i].at < nextArrival)
                    nextArrival = p[i].at;
            }

            ganttTime[ganttCount] = t;
            strcpy(ganttLabel[ganttCount], "IDLE");
            ganttCount++;

            t = nextArrival;
            continue;
        }

        // Record start in Gantt
        ganttTime[ganttCount] = t;
        strcpy(ganttLabel[ganttCount], "");
        ganttLabel[ganttCount][0] = 'P';
        ganttLabel[ganttCount][1] = p[idx].id;
        ganttLabel[ganttCount][2] = '\0';
        ganttCount++;

        // Execute process
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
    cout << "\n\nID\tAT\tBT\tPRIO\tCT\tTAT\tWT";
    cout << "\n----------------------------------------------\n";
    for (i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].prio << "\t"
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
