// BLOCK 1
#include <iostream.h>
#include <conio.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt, rt, done, prio;    
};

void main() {
    clrscr();

    int n, i, j;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[20];

    for(i = 0; i < n; i++){
        cout << "\nEnter Process ID: ";
        cin >> p[i].id;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time: ";
        cin >> p[i].bt;
        cout << "Priority (lower = higher priority): ";
        cin >> p[i].prio;

        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    // sort by arrival
    for(i = 0; i < n - 1; i++){
        for(j = i + 1; j < n; j++){
            if(p[i].at > p[j].at){
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // BLOCK 2

    int t = 0, completed = 0, busy = 0;
    float avgtat = 0, avgwt = 0;

    int ganttOrder[100], ganttTime[100];
    int ganttCount = 0;

    while(completed < n){
        int idx = -1;
        int bestPrio = 9999;

        // choose highest priority among ready processes
        for(i = 0; i < n; i++){
            if(p[i].at <= t && p[i].done == 0 && p[i].rt > 0){

                if(p[i].prio < bestPrio){
                    bestPrio = p[i].prio;
                    idx = i;
                }
                // tie: earlier arrival
                else if(p[i].prio == bestPrio && p[i].at < p[idx].at){
                    idx = i;
                }
            }
        }

        // IDLE CPU
        if(idx == -1){
            int nextArrival = 9999;
            for(i = 0; i < n; i++){
                if(p[i].done == 0 && p[i].at < nextArrival)
                    nextArrival = p[i].at;
            }

            ganttOrder[ganttCount] = -1;  
            ganttTime[ganttCount] = t;
            ganttCount++;

            t = nextArrival;
            continue;
        }

        // record execution in gantt
        ganttOrder[ganttCount] = idx;
        ganttTime[ganttCount] = t;
        ganttCount++;

        // run for 1 time unit
        p[idx].rt--;
        t++;
        busy++;

        // process finished
        if(p[idx].rt == 0){
            p[idx].done = 1;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    // BLOCK 3
    cout << "\n\nID\tAT\tBT\tPRIO\tCT\tTAT\tWT";
    cout << "\n---------------------------------------------------\n";

    for(i = 0; i < n; i++){
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

    int totalTime = t;
    float cpu = (busy * 100.0) / totalTime;

    cout << "\nAVG TAT: " << avgtat / n;
    cout << "\nAVG WT: " << avgwt / n;
    cout << "\nCPU UTIL: " << cpu << "%";

    // BLOCK 4 
    cout << "\n\nGANTT CHART\n";

    for(i = 0; i < ganttCount; i++){
        if(i == 0 || ganttOrder[i] != ganttOrder[i - 1]) {
            if(ganttOrder[i] == -1)
                cout << "|  IDLE  ";
            else
                cout << "|  P" << p[ganttOrder[i]].id << "  ";
        }
    }
    cout << "|\n";

    for(i = 0; i < ganttCount; i++){
        if(i == 0 || ganttOrder[i] != ganttOrder[i - 1])
            cout << ganttTime[i] << "\t";
    }
    cout << t;

    getch();
}
