// BLOCK 1
#include <iostream.h>
#include <conio.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt, rt; // rt = remaining time
};

void main() {
    clrscr();

    int n, i, j, time = 0, tq;
    float avgtat = 0, avgwt = 0;
    int busy = 0;

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
        p[i].rt = p[i].bt; // initialize remaining time
    }

    // Sort processes by arrival time
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
    cout << "\nEnter Time Quantum: ";
    cin >> tq; // Maximum time each process can run in one cycle

    int completed = 0;     
    int done;               // Flag to check if any process can run
    char ganttProcess[100]; 
    int ganttTime[100];    
    int ganttIndex = 0;     

    // Keep looping until all processes are completed
    while (completed < n) {
        done = 1; // Assume no process can run at current time

        // Go through all processes to see who can run
        for (i = 0; i < n; i++) {
            // Process can run if it has remaining time and has already arrived
            if (p[i].rt > 0 && p[i].at <= time) {

                done = 0; // Found a process that can run

                // If the process needs more time than the quantum, run only one cycle
                if (p[i].rt > tq) {
                    time += tq;       // Advance current time
                    busy += tq;       // CPU was busy
                    p[i].rt -= tq;    // Reduce the remaining time of the process by the cycle length (tq)

                } else { // If the process will finish in this cycle
                    time += p[i].rt;
                    busy += p[i].rt;
                    p[i].rt = 0;      // Process finished

                    // Calculate completion, turnaround, and waiting times
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    completed++;        // Count this process as completed
                }

                ganttProcess[ganttIndex] = p[i].id;
                ganttTime[ganttIndex] = time;
                ganttIndex++;
            }
        }

        // If no process can run, move time forward (CPU idle)
        if (done == 1) {
            time++;

            ganttProcess[ganttIndex] = 'I'; // IDLE indicator
            ganttTime[ganttIndex] = time;
            ganttIndex++;
        }
    }

// BLOCK 3
    cout << "\n\nID\tAT\tBT\tCT\tTAT\tWT\n";
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

    int totalTime = 0;
    for (i = 0; i < n; i++) {
        if (p[i].ct > totalTime)
            totalTime = p[i].ct;
    }

    float cpu = (busy * 100.0) / totalTime;

    cout << "\nAverage TAT: " << avgtat / n;
    cout << "\nAverage WT: " << avgwt / n;
    cout << "\nCPU Utilization: " << cpu << "%";

// BLOCK 4
    cout << "\n\nGantt Chart:\n";

    // Print process boxes
    for (i = 0; i < ganttIndex; i++) {
        if (ganttProcess[i] == 'I')
            cout << "| IDLE ";
        else
            cout << "| P" << ganttProcess[i] << " ";
    }
    cout << "|\n";

    // Print timeline below
    int prev = 0;
    cout << prev;
    for (i = 0; i < ganttIndex; i++) {
        cout << "   " << ganttTime[i];
    }

    getch();
}
