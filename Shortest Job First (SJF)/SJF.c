#include <stdio.h>
#include <string.h>

int main() {
    int n, i, time = 0, completed = 0;
    char pid[20][20];
    int at[20], bt[20], ct[20], tat[20], wt[20], done[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i=0;i<n;i++) {
        printf("\nProcess %d ID: ", i+1);
        scanf("%s", pid[i]);
        printf("Arrival Time of %s: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Burst Time of %s: ", pid[i]);
        scanf("%d", &bt[i]);
        done[i] = 0;
    }

    printf("\nGantt Chart:\n|");

    // Scheduling
    while(completed < n) {
        int min = 9999, idx = -1;

        for(i=0;i<n;i++) {
            if(at[i] <= time && done[i] == 0) {
                if(bt[i] < min) {
                    min = bt[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {   // CPU Idle
            printf(" IDLE |");
            time++;
        } else {
            printf(" %s |", pid[idx]);
            time = time + bt[idx];
            ct[idx] = time;
            done[idx] = 1;
            completed++;
        }
    }

    // Calculate TAT and WT
    for(i=0;i<n;i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Time stamps
    printf("\n0");
    time = 0;
    completed = 0;

    while(completed < n) {
        int next = 9999;
        for(i=0;i<n;i++) {
            if(ct[i] > time && ct[i] < next)
                next = ct[i];
        }
        if(next == 9999) break;
        printf("   %d", next);
        time = next;
        completed++;
    }

    // Table
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}
