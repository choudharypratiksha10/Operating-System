#include <stdio.h>
#include <string.h>

int main() {
    int n, i, time = 0, completed = 0;
    char pid[10][10];
    int at[10], bt[10], rt[10];
    int ct[10], tat[10], wt[10];
    int done[10] = {0};

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess ID: ");
        scanf("%s", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // remaining time
    }

    printf("\nGantt Chart:\n|");

    while(completed < n) {
        int shortest = -1;
        int min_rt = 9999;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            printf(" IDLE |");
            time++;
            continue;
        }

        printf(" %s |", pid[shortest]);
        rt[shortest]--;
        time++;

        if(rt[shortest] == 0) {
            ct[shortest] = time;
            completed++;
        }
    }

    printf("\n0");
    for(i = 1; i <= time; i++)
        printf("   %d", i);

    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
