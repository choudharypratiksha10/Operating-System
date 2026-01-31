import java.util.Scanner;

class FCFS {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        int n, i, j;
        System.out.print("Enter number of processes: ");
        n = sc.nextInt();

        String pid[] = new String[n];
        int at[] = new int[n];
        int bt[] = new int[n];
        int ct[] = new int[n];
        int tat[] = new int[n];
        int wt[] = new int[n];
        int pos[] = new int[n];

        for(i = 0; i < n; i++) {
            pos[i] = i;

            System.out.print("\nProcess " + (i+1) + " ID: ");
            pid[i] = sc.next();

            System.out.print("Arrival Time of " + pid[i] + ": ");
            at[i] = sc.nextInt();

            System.out.print("Burst Time of " + pid[i] + ": ");
            bt[i] = sc.nextInt();
        }

        // Sorting by Arrival Time
        for(i = 0; i < n-1; i++) {
            for(j = i+1; j < n; j++) {
                if(at[i] > at[j] || (at[i] == at[j] && pos[i] > pos[j])) {
                    int temp;
                    String tpid;

                    temp = at[i];
                    at[i] = at[j];
                    at[j] = temp;

                    temp = bt[i];
                    bt[i] = bt[j];
                    bt[j] = temp;

                    temp = pos[i];
                    pos[i] = pos[j];
                    pos[j] = temp;

                    tpid = pid[i];
                    pid[i] = pid[j];
                    pid[j] = tpid;
                }
            }
        }

        // Completion Time
        if(at[0] > 0)
            ct[0] = at[0] + bt[0];
        else
            ct[0] = bt[0];

        for(i = 1; i < n; i++) {
            if(ct[i-1] < at[i])
                ct[i] = at[i] + bt[i];
            else
                ct[i] = ct[i-1] + bt[i];
        }

        float avg_wt = 0, avg_tat = 0;

        // TAT and WT
        for(i = 0; i < n; i++) {
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
            avg_wt = avg_wt + wt[i];
            avg_tat = avg_tat + tat[i];
        }

        // -------- GANTT CHART WITH IDLE --------
        System.out.println("\nGantt Chart:");
        System.out.print("|");

        int time = 0;

        for(i = 0; i < n; i++) {
            if(time < at[i]) {
                System.out.print(" IDLE |");
                time = at[i];
            }

            System.out.print(" " + pid[i] + " |");
            time = ct[i];
        }

        System.out.print("\n0");
        time = 0;

        for(i = 0; i < n; i++) {
            if(time < at[i]) {
                System.out.print("   " + at[i]);
                time = at[i];
            }

            System.out.print("   " + ct[i]);
            time = ct[i];
        }
        System.out.println();

        // Table
        System.out.println("\nPID\tAT\tBT\tCT\tTAT\tWT");
        for(i = 0; i < n; i++) {
            System.out.println(pid[i] + "\t" + at[i] + "\t" + bt[i] + "\t" +
                               ct[i] + "\t" + tat[i] + "\t" + wt[i]);
        }

        System.out.println("\nAverage Turnaround Time = " + (avg_tat/n));
        System.out.println("Average Waiting Time = " + (avg_wt/n));
    }
}
