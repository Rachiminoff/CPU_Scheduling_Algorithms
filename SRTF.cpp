//BLOCK 1
#include <iostream.h>
#include <conio.h>

class Process {
public:
    char id;
    int at, bt, ct, tat, wt, done;
    int rt; // NEW for SRTF: remaining time (keeps track of how much burst time is left)
};

void main() {
    clrscr();

    int n, i, j;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[20];

    // Input process data
    for(i = 0; i < n; i++){
        cout << "\nEnter Process ID: ";
        cin >> p[i].id;
        cout << "Enter Arrival Time: ";
        cin >> p[i].at;
        cout << "Enter Burst Time: ";
        cin >> p[i].bt;

        p[i].rt = p[i].bt; // NEW for SRTF: remaining time starts equal to burst time
        p[i].done = 0; // 0 means not yet completed
    }

    // Sort by Arrival Time (bubble sort)
    for(i = 0; i < n - 1; i++){
        for(j = i + 1; j < n; j++){
            if(p[i].at > p[j].at){
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

//BLOCK 2
    // --- NEW LOGIC SECTION STARTS HERE ---
    int t = 0,  completed = 0, busy = 0;          
    float avgtat = 0, avgwt = 0;

    int ganttOrder[100], ganttTime[100]; 
    int ganttCount = 0;

    while(completed < n){
        int idx = -1;         
        int min_rt = 9999;    // used to find the process with smallest remaining time

        for(i = 0; i < n; i++){
            if(p[i].at <= t && p[i].done == 0 // find the process that has already arrived (at <= t), is not done yet, 
                && p[i].rt > 0               // still has remaining time left, 
                && p[i].rt < min_rt){       // and has the smallest remaining time so far (rt < min_rt)
                    
                min_rt = p[i].rt;
                idx = i;
            }
        }

        if(idx == -1){
            t++;
            continue;
        }

        ganttOrder[ganttCount] = idx;
        ganttTime[ganttCount] = t;
        ganttCount++;

        // Process runs for 1 time unit
        p[idx].rt--;
        t++;
        busy++;

        // If process finishes after this time unit
        if(p[idx].rt == 0){
            p[idx].done = 1;
            p[idx].ct = t; // completion time
            p[idx].tat = p[idx].ct - p[idx].at; // turnaround time
            p[idx].wt = p[idx].tat - p[idx].bt; // waiting time
            completed++;
        }
    }
    // --- NEW LOGIC SECTION ENDS HERE ---

//BLOCK 3

    // Display process table
    cout << "\n\nID\tAT\tBT\tCT\tTAT\tWT";
    cout << "\n--------------------------------------------\n";

    for(i = 0; i < n; i++){
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";

        avgtat += p[i].tat;
        avgwt += p[i].wt;
    }

    // Compute total time for CPU Utilization (same as SJF)
    int totalTime = 0;
    for(i = 0; i < n; i++){
        if(p[i].ct > totalTime){
            totalTime = p[i].ct;
        }
    }

    float cpu = (busy * 100.0) / totalTime;

    cout << "\nAverage Turnaround Time: " << (avgtat / n);
    cout << "\nAverage Waiting Time   : " << (avgwt / n);
    cout << "\nCPU Utilization        : " << cpu << "%";

//BLOCK 4

    cout << "\n\nGANTT CHART:\n";

    if(ganttTime[0] != 0){
        cout << "|       ";
    }

    for(i = 0; i < ganttCount; i++){                      // adjacent = right next to each other
        if(i == 0 || ganttOrder[i] != ganttOrder[i - 1]){ // NEW: avoid showing the same process twice in a row (duplicates allowed if not adjacent)
            cout << "|  P" << p[ganttOrder[i]].id << "   ";
        }
    }
    cout << "|\n";

    if(ganttTime[0] != 0){
        cout << "0\t";
    }

    for(i = 0; i < ganttCount; i++){
        if(i == 0 || ganttOrder[i] != ganttOrder[i - 1]){ // NEW
            cout << ganttTime[i] << "\t";
        }
    }
    cout << t << "\n";

    getch();
}