#include <stdio.h>

struct Process
{
    int id, bt, deadline, rt, ct, tat, wt;
};
void gantt(int tl[], int len)
{
    printf("\nGantt Chart:\n");

    for(int i = 0; i < len; i++)
    {
        printf("| P%d ", tl[i]);
    }

    printf("|\n");

    for(int i = 0; i <= len; i++)
    {
        printf("%d    ", i);
    }

    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int tl[1000];

    for(int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("BT and Deadline of P%d: ", i + 1);
        scanf("%d %d", &p[i].bt, &p[i].deadline);

        p[i].rt = p[i].bt;
    }

    int completed = 0, t = 0;

    while(completed < n)
    {
        int idx = -1;
        int min = 99999;

        for(int i = 0; i < n; i++)
        {
            if(p[i].rt > 0 && p[i].deadline < min)
            {
                min = p[i].deadline;
                idx = i;
            }
        }
        if (idx != -1) {
            tl[t] = p[idx].id;
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

    printf("\nID\tBT\tDL\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,p[i].bt,p[i].deadline,
               p[i].ct,p[i].wt,p[i].tat);
    }
    gantt(tl, t);

    return 0;
}