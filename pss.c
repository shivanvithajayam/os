#include <stdio.h>

#define MAX 100

struct Process
{
    int id;
    int bt;
    int share;
    int rt;
    int ct;
    int tat;
    int wt;
};

void ProportionalShare(struct Process p[], int n)
{
    int completed = 0;
    int time = 0;
    int tl[1000];

    for(int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while(completed < n)
    {
        for(int i = 0; i < n; i++)
        {
            if(p[i].rt > 0)
            {
                int timeSlice = p[i].share;

                if(p[i].rt < timeSlice)
                    timeSlice = p[i].rt;

                for(int j = 0; j < timeSlice; j++)
                {
                    tl[time] = p[i].id;
                    time++;
                }

                p[i].rt -= timeSlice;

                if(p[i].rt == 0)
                {
                    p[i].ct = time;
                    p[i].tat = p[i].ct;   // AT = 0
                    p[i].wt = p[i].tat - p[i].bt;

                    completed++;
                }
            }
        }
    }

    printf("\nProportional Share Scheduling\n");
    printf("ID\tBT\tShare\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].bt,
               p[i].share,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }

    printf("\nGantt Chart:\n");

    for(int i = 0; i < time; i++)
        printf("| P%d ", tl[i]);

    printf("|\n");

    for(int i = 0; i <= time; i++)
        printf("%d\t", i);

    printf("\n");
}

int main()
{
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        p[i].id = i + 1;

        printf("Enter BT and Share of P%d: ", i + 1);
        scanf("%d %d", &p[i].bt, &p[i].share);
    }

    ProportionalShare(p, n);

    return 0;
}