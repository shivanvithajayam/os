#include <stdio.h>

#define MAX 10

struct process
{
    int at, bt;
    int ct, wt, tat;
    int done;
};

void sjf(struct process p[], int n)
{
    int t = 0;
    int gantt[MAX];
    int g = 0;
    float total_wt = 0, total_tat = 0;

    int completed = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].done == 0)
            {
                if (p[i].bt < min_bt)
                {
                    min_bt = p[i].bt;
                    idx = i;
                }
                else if (p[i].bt == min_bt)
                {
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx != -1)
        {
            p[idx].wt = t - p[idx].at;
            p[idx].ct = t + p[idx].bt;
            p[idx].tat = p[idx].bt + p[idx].wt;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;

            p[idx].done = 1;
            gantt[g++] = idx;
            completed++;
            t = p[idx].ct;
        }
        else
        {
            t++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }
    printf("\nGantt Chart:\n\n");

    printf("|");
    for(int i = 0; i < g; i++)
    {
        printf(" P%d |", gantt[i] + 1);
    }

    printf("\n0");

    for(int i = 0; i < g; i++)
    {
        printf("    %d", p[gantt[i]].ct);
    }
    printf("\n");

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main()
{
    int n;
    struct process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].done = 0;
    }

    sjf(p, n);

    return 0;
}