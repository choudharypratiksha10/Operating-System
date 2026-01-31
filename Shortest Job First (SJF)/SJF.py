# Input number of processes
n = int(input("Enter number of processes: "))

pid = []
at = []
bt = []
ct = []
tat = []
wt = []
done = []

for i in range(n):
    pid.append(input("Process " + str(i+1) + " ID: "))
    at.append(int(input("Arrival Time of " + pid[i] + ": ")))
    bt.append(int(input("Burst Time of " + pid[i] + ": ")))
    ct.append(0)
    tat.append(0)
    wt.append(0)
    done.append(0)

time = 0
completed = 0
avg_wt = 0
avg_tat = 0

print("\nGantt Chart:")
print("|", end="")

# Scheduling
while completed < n:
    min_bt = 9999
    idx = -1

    for i in range(n):
        if at[i] <= time and done[i] == 0:
            if bt[i] < min_bt:
                min_bt = bt[i]
                idx = i

    if idx == -1:
        print(" IDLE |", end="")
        time += 1
    else:
        print(" " + pid[idx] + " |", end="")
        time += bt[idx]
        ct[idx] = time
        done[idx] = 1
        completed += 1

# TAT and WT
for i in range(n):
    tat[i] = ct[i] - at[i]
    wt[i] = tat[i] - bt[i]
    avg_wt += wt[i]
    avg_tat += tat[i]

# Time stamps
print("\n0", end="")
times = sorted(ct)
for t in times:
    print("   " + str(t), end="")
print()

# Table
print("\nPID\tAT\tBT\tCT\tTAT\tWT")
for i in range(n):
    print(pid[i], "\t", at[i], "\t", bt[i], "\t", ct[i], "\t", tat[i], "\t", wt[i])

print("\nAverage Turnaround Time =", avg_tat/n)
print("Average Waiting Time =", avg_wt/n)
