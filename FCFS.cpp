//block 1

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
    cout << "Number of processes: ";
    cin >> n;

    Process p[20];

    // Input
    for(i = 0; i < n; i++) {
        cout << "\nEnter Process ID: ";
        cin >> p[i].id;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time: ";
        cin >> p[i].bt;
    }

    // Sort by Arrival Time (bubble sort)
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

//block 2
    int t = 0, busy = 0;
    float avgtat = 0, avgwt = 0;

    // Compute CT, TAT, WT
    for(i = 0; i < n; i++) {
        if(t < p[i].at) {
            t = p[i].at; // CPU idle if process not arrived
        }

        p[i].ct = t + p[i].bt;
        t = p[i].ct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        busy += p[i].bt;
    }

//block 3
    // Display Table
    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "----------------------------------------\n";
    for(i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
    }

    // Averages & CPU Utilization
    for(i = 0; i < n; i++) {
        avgtat += p[i].tat;
        avgwt  += p[i].wt;
    }

    int totalTime = p[n-1].ct - p[0].at;
    float cpuUtilization = (busy * 100.0) / totalTime;

    cout << "\nAverage Turnaround Time: " << avgtat / n;
    cout << "\nAverage Waiting Time   : " << avgwt / n;
    cout << "\nCPU Utilization        : " << cpuUtilization << "%\n";

//block 4
    // Gantt Chart
    cout << "\nGantt Chart:\n";

    // Process bars
    for(i = 0; i < n; i++) {
        cout << "|  P" << p[i].id << "  ";
    }
    cout << "|\n";

    // Timeline
    cout << p[0].at;
    for(i = 0; i < n; i++) {
        cout << "\t" << p[i].ct;
    }
    cout << "\n";

    getch();
}
