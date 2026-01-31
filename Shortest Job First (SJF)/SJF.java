import java.util.Scanner;

class SJF {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        int n, i;
        System.out.print("Enter number of processes: ");
        n = sc.nextInt();

        String pid[] = new String[n];
        int at[] = new int[n];
        int bt[] = new int[n];
        int ct[] = new int[n];
        int tat[] = new int[n];
        int wt[] = new int[n];
        int done[] = new int[n];

        for(i=0;i<n;i++) {
            System.out.print("\nProcess " + (i+1) + " ID: ");
            pid[i] = sc.next();
            System.out.print("Arrival Time of " + pid[i] + ": ");
            at[i] = sc.nextInt();
            System.out.print("Burst Time of " + pid[i] + ": ");
            bt[i] = sc.nextInt();
            done[i] = 0;
        }

        int time = 0, completed = 0;
        float avg_wt = 0, avg_tat = 0;

        System.out.println("\nGantt Chart:");
        System.out.print("|");

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

            if(idx == -1) {
                System.out.print(" IDLE |");
                time++;
            } else {
                System.out.print(" " + pid[idx] + " |");
                time = time + bt[idx];
                ct[idx] = time;
                done[idx] = 1;
                completed++;
            }
        }

        for(i=0;i<n;i++) {
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
            avg_wt += wt[i];
            avg_tat += tat[i];
        }

        System.out.print("\n0");
        int temp[] = ct.clone();
        java.util.Arrays.sort(temp);
        for(i=0;i<n;i++)
            System.out.print("   " + temp[i]);

        System.out.println("\n\nPID\tAT\tBT\tCT\tTAT\tWT");
        for(i=0;i<n;i++) {
            System.out.println(pid[i] + "\t" + at[i] + "\t" + bt[i] + "\t" +
                               ct[i] + "\t" + tat[i] + "\t" + wt[i]);
        }

        System.out.println("\nAverage Turnaround Time = " + (avg_tat/n));
        System.out.println("Average Waiting Time = " + (avg_wt/n));
    }
}
