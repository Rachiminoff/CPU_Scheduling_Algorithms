// BLOCK 1

#include <iostream.h>
#include <conio.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt;
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

    int t = 0, busy = 0;
    float avgtat = 0, avgwt = 0;

    // FCFS logic with idle support
    for (i = 0; i < n; i++) {
        if (t < p[i].at) {   // CPU is idle until this process arrives
            t = p[i].at;
        }
        p[i].ct = t + p[i].bt;
        t = p[i].ct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        busy += p[i].bt;
    }

// BLOCK 3

    // Print table
    cout << "\n\nID\tAT\tBT\tCT\tTAT\tWT";
    cout << "\n-----------------------------------------------\n";
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

    int totalTime = p[n - 1].ct;
    float cpu = (busy * 100.0) / totalTime;

    cout << "\nAVG TAT: " << avgtat / n;
    cout << "\nAVG WT: " << avgwt / n;
    cout << "\nCPU UTIL: " << cpu << "%";

// BLOCK 4

    // Gantt chart with idle time shown
    cout << "\n\nGANTT CHART\n";

    t = 0;
    for (i = 0; i < n; i++) {
        if (t < p[i].at) {
            cout << "|  IDLE  ";
            t = p[i].at;
        }
        cout << "|  P" << p[i].id << "  ";
        t += p[i].bt;
    }
    cout << "|\n";

    t = 0;
    cout << p[0].at;
    for (i = 0; i < n; i++) {
        if (t < p[i].at) {
            t = p[i].at;
            cout << "\t" << t; // after idle
        }
        t += p[i].bt;
        cout << "\t" << t;
    }

    getch();
}
