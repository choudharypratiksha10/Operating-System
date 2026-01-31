n = int(input("Enter number of processes: "))

pid = []
at = []
bt = []
ct = []
tat = []
wt = []
pos = []

for i in range(n):
    pos.append(i)
    pid.append(input("Process " + str(i+1) + " ID: "))
    at.append(int(input("Arrival Time of " + pid[i] + ": ")))
    bt.append(int(input("Burst Time of " + pid[i] + ": ")))
    ct.append(0)
    tat.append(0)
    wt.append(0)

# Sorting by Arrival Time
for i in range(n-1):
    for j in range(i+1, n):
        if at[i] > at[j] or (at[i] == at[j] and pos[i] > pos[j]):
            temp = at[i]
            at[i] = at[j]
            at[j] = temp

            temp = bt[i]
            bt[i] = bt[j]
            bt[j] = temp

            temp = pos[i]
            pos[i] = pos[j]
            pos[j] = temp

            temp = pid[i]
            pid[i] = pid[j]
            pid[j] = temp

# Completion Time
if at[0] > 0:
    ct[0] = at[0] + bt[0]
else:
    ct[0] = bt[0]

for i in range(1, n):
    if ct[i-1] < at[i]:
        ct[i] = at[i] + bt[i]
    else:
        ct[i] = ct[i-1] + bt[i]

avg_wt = 0
avg_tat = 0

# TAT and WT
for i in range(n):
    tat[i] = ct[i] - at[i]
    wt[i] = tat[i] - bt[i]
    avg_wt = avg_wt + wt[i]
    avg_tat = avg_tat + tat[i]

# -------- GANTT CHART WITH IDLE --------
print("\nGantt Chart:")
print("|", end="")

time = 0

for i in range(n):
    if time < at[i]:
        print(" IDLE |", end="")
        time = at[i]

    print(" " + pid[i] + " |", end="")
    time = ct[i]

print("\n0", end="")
time = 0

for i in range(n):
    if time < at[i]:
        print("   " + str(at[i]), end="")
        time = at[i]

    print("   " + str(ct[i]), end="")
    time = ct[i]

print()

# Table
print("\nPID\tAT\tBT\tCT\tTAT\tWT")
for i in range(n):
    print(pid[i], "\t", at[i], "\t", bt[i], "\t", ct[i], "\t", tat[i], "\t", wt[i])

print("\nAverage Turnaround Time =", avg_tat/n)
print("Average Waiting Time =", avg_wt/n)