// BLOCK 1
#include <iostream.h>
#include <conio.h>

class Process {
public:
   char id;
   int at, bt, ct, tat, wt, done, rt;
};

void main(){
    clrscr();

    int n, i, j;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[20];

    for(i = 0; i < n; i++){
        cout << "\nEnter Process ID: ";
        cin >> p[i].id;
        cout << "Enter Arrival Time: ";
        cin >> p[i].at;
        cout << "Enter Burst Time: ";
        cin >> p[i].bt;

        p[i].done = 0;
        p[i].rt = p[i].bt;
    }

    // bubble sort
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

    int t = 0, busy = 0, completed = 0;
    float avgtat = 0, avgwt = 0;

    int ganttOrder[100], ganttTime[100];
    int ganttCount = 0;

    while(completed < n){
        int idx = -1;
        int min_rt = 9999;

        for(i = 0; i < n; i++){
            if(p[i].at <= t && p[i].done == 0 && p[i].rt > 0 && p[i].rt < min_rt){
                    min_rt = p[i].rt;
                    idx = i;
                }
        }

        // handle idle time
        if(idx == -1){
            int nextArrival = 9999;
            for(i = 0; i < n; i++){
                if(p[i].done == 0 && p[i].at < nextArrival)
                    nextArrival = p[i].at;
            }

            ganttOrder[ganttCount] = -1; // mark idle
            ganttTime[ganttCount] = t;
            ganttCount++;

            t = nextArrival; // jump to next arrival
            continue;
        }

        ganttOrder[ganttCount] = idx;
        ganttTime[ganttCount] = t;
        ganttCount++;

        p[idx].rt--;
        t++;
        busy++;

        if(p[idx].rt == 0){
            p[idx].done = 1;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    // BLOCK 3
    cout << "\n\nID\tAT\tBT\tCT\tTAT\tWT";
    cout << "\n-----------------------------------------------\n";
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

    int totalTime = 0;
    for(i = 0; i < n; i++){
	if(p[i].ct > totalTime){
            totalTime = p[i].ct;
        }
    }

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
      if(i == 0 || ganttOrder[i] != ganttOrder[i - 1]){
        cout << ganttTime[i] << "\t";
      }
    }
    cout << t;

    getch();
}
