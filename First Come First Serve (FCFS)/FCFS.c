#include <stdio.h>
#include <string.h>

int main() {
    int n, i, j;
    char pid[20][20];
    int at[20], bt[20], ct[20], tat[20], wt[20];
    int pos[20];

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pos[i] = i;

        printf("\nProcess %d ID: ", i + 1);
        scanf("%s", pid[i]);

        printf("Arrival Time of %s: ", pid[i]);
        scanf("%d", &at[i]);

        printf("Burst Time of %s: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    /* Sort by Arrival Time */
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j] || (at[i] == at[j] && pos[i] > pos[j])) {
                int temp;
                char tpid[20];

                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pos[i]; pos[i] = pos[j]; pos[j] = temp;

                strcpy(tpid, pid[i]);
                strcpy(pid[i], pid[j]);
                strcpy(pid[j], tpid);
            }
        }
    }

    /* Completion Time */
    if (at[0] > 0)
        ct[0] = at[0] + bt[0];
    else
        ct[0] = bt[0];

    for (i = 1; i < n; i++) {
        if (ct[i - 1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];
    }

    /* TAT & WT */
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    /* Gantt Chart with IDLE */
    printf("\nGantt Chart:\n|");

    int time = 0;

    for (i = 0; i < n; i++) {
        if (time < at[i]) {
            printf(" IDLE |");
            time = at[i];
        }

        printf(" %s |", pid[i]);
        time = ct[i];
    }

    printf("\n0");
    time = 0;

    for (i = 0; i < n; i++) {
        if (time < at[i]) {
            printf("   %d", at[i]);
            time = at[i];
        }

        printf("   %d", ct[i]);
        time = ct[i];
    }

    /* Table */
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}