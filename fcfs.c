#include <stdio.h>

#define MAX 10

struct process
{
    int at, bt;
    int wt, tat, ct;
};
void sortProcesses(struct process p[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
void FCFS(struct process p[], int n)
{
    sortProcesses(p, n);

    int t = 0;

    for (int i = 0; i < n; i++)
    {
        if (t < p[i].at)//this is simply a condition that checks whether the CPU is idle before the next process arrives.
            t = p[i].at;

        p[i].wt = t - p[i].at;
        p[i].ct = t + p[i].bt;
        p[i].tat = p[i].bt + p[i].wt;

        t = p[i].ct;
    }

    float awt = 0, atat = 0;

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].wt,
               p[i].tat);

        awt += p[i].wt;
        atat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", awt / n);
    printf("\nAverage Turnaround Time = %.2f\n", atat / n);
}
void printGanttChart(struct process p[], int n)
    {
        printf("\nGantt Chart:\n");
        printf("-------------------------------------------------\n");

        // Print process IDs
        for (int i = 0; i < n; i++)
        {
            printf("|  P%d  ", i+1);
        }
        printf("|\n");

        printf("-------------------------------------------------\n");

        // Print timeline
        
        printf("%d", p[0].at < 0 ? 0 : p[0].at); // start time
        for (int i = 0; i < n; i++)
        {
            printf("     %d", p[i].ct);
        }
        printf("\n");
    }

int main()
{
    int n;
    struct process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    FCFS(p, n);
    printGanttChart(p,n);

    return 0;
}