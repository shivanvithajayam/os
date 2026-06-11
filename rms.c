#include <stdio.h>

struct Process
{
    int id, bt, period, rt, ct, tat, wt;
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++)
    {
        p[i].id = i + 1;

        printf("BT and Period of P%d: ", i + 1);
        scanf("%d %d", &p[i].bt, &p[i].period);

        p[i].rt = p[i].bt;
    }

    int completed = 0, t = 0;

    while(completed < n)
    {
        int idx = -1;
        int min = 99999;

        for(int i = 0; i < n; i++)
        {
            if(p[i].rt > 0 && p[i].period < min)
            {
                min = p[i].period;
                idx = i;
            }
        }
        
        if (idx != -1) {
            p[idx].rt--;
            t++;

            if (p[idx].rt == 0) {
                
                p[idx].ct = t;
                p[idx].tat = p[idx].ct;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        } 
        else {
 
            t++;
        }
    }

    printf("\nID\tBT\tPeriod\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,p[i].bt,p[i].period,
               p[i].ct,p[i].wt,p[i].tat);
    }

    return 0;
}