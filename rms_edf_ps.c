#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

struct Process {
    int id;
    int bt;
    int deadline; // For EDF
    int period;
    int share;   // For RMS
    int ct, wt, tat, rt;
};

// Utility function: reset metrics
void resetProcesses(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].ct = p[i].wt = p[i].tat = 0;
    }
}

// Function to print Gantt Chart
void printGanttChart(int timeline[], int totalTime) {
    printf("\n===== Gantt Chart =====\n");

    // Print process IDs in timeline
    for (int i = 0; i < totalTime; i++) {
        if (timeline[i] == -1)
            printf("| Idle ");
        else
            printf("| P%d ", timeline[i]);
    }
    printf("|\n");

    // Print time markers
    for (int i = 0; i <= totalTime; i++) {
        printf("%d\t", i);
    }
    printf("\n");
}

// ------------------ 1. EDF Scheduling ------------------
void EDF_preemptive(struct Process p[], int n) {
    printf("\n===== Preemptive EDF Scheduling =====\n");

    int completed = 0, time = 0;
    int timeline[1000];
    int totalTime = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int idx = -1;
        int minDeadline = 1e9;

        // Find process with earliest deadline
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].deadline < minDeadline) {
                minDeadline = p[i].deadline;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].rt--;  // execute for 1 unit
            timeline[time] = p[idx].id;
            time++;
            totalTime = time;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            timeline[time] = -1; // idle
            time++;
            totalTime = time;
        }
    }

    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);

    printGanttChart(timeline, totalTime);
}

// ------------------ 2. Rate Monotonic Scheduling (RMS) ------------------
void RMS_preemptive(struct Process p[], int n) {
    printf("\n===== Preemptive RMS Scheduling =====\n");

    int completed = 0, time = 0;
    int timeline[1000];
    int totalTime = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int idx = -1;
        int minPeriod = 1e9;

        // Find process with smallest period
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].period < minPeriod) {
                minPeriod = p[i].period;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            timeline[time] = p[idx].id;
            time++;
            totalTime = time;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            timeline[time] = -1; // idle
            time++;
            totalTime = time;
        }
    }

    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);

    printGanttChart(timeline, totalTime);
}

// ------------------ 3. Utilization Check ------------------
void utilizationCheck(struct Process p[], int n) {
    double U_rms = 0, U_edf = 0;
    for (int i = 0; i < n; i++) {
        U_rms += (double)p[i].bt / p[i].period;
        U_edf += (double)p[i].bt / p[i].deadline;
    }

    double bound_rms = n * (pow(2.0, 1.0/n) - 1);

    printf("\n===== Utilization Analysis =====\n");
    printf("Total Utilization (RMS): %.2f\n", U_rms);
    printf("RMS Bound for %d tasks: %.2f\n", n, bound_rms);
    if (U_rms <= bound_rms)
        printf("Schedulable under RMS\n");
    else
        printf("May NOT be schedulable under RMS\n");

    printf("\nTotal Utilization (EDF): %.2f\n", U_edf);
    if (U_edf <= 1.0)
        printf("Schedulable under EDF\n");
    else
        printf("Not schedulable under EDF\n");
}
void ProportionalShare(struct Process p[], int n) {
printf("\n===== Proportional Share Scheduling =====\n");
int totalShare = 0, totalBT = 0;
for (int i = 0; i < n; i++)
{
totalShare += p[i].share;
totalBT += p[i].bt;
}
// Simulate Round Robin according to weights
int time = 0, remaining[MAX];
for (int i = 0; i < n; i++)
remaining[i] = p[i].bt;
int done = 0;
while (done < n)
{
for (int i = 0; i < n; i++)
{
if (remaining[i] > 0)
{
int timeSlice = (p[i].share > 0) ? 1 : 0;
if (remaining[i] < timeSlice) timeSlice = remaining[i];
time += timeSlice;
remaining[i] -= timeSlice;
if (remaining[i] == 0)
{
p[i].ct = time;

p[i].tat = p[i].ct;
p[i].wt = p[i].tat - p[i].bt;
done++;
}
}
}
}
printf("ID\tBT\tShare\tCT\tWT\tTAT\n");
for (int i = 0; i < n; i++)
printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].bt, p[i].share,
p[i].ct, p[i].wt, p[i].tat);
}

// ------------------ Main ------------------
int main() {
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
        printf("Share (for Proportional): ");
scanf("%d", &p[i].share);
    }

    // Run EDF
    resetProcesses(p, n);
    EDF_preemptive(p, n);

    // Run RMS
    resetProcesses(p, n);
    RMS_preemptive(p, n);

    // Utilization check
    utilizationCheck(p, n);
    resetProcesses(p, n);
ProportionalShare(p, n);

    return 0;
}
 