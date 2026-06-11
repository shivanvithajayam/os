#include <stdio.h>
#define MAX 10

struct process {
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int rt;
};

void srtf(struct process p[], int n) {
    int completed = 0, t = 0;
    float total_tat = 0, total_wt = 0;

    while (completed < n) {
        int idx = -1;
        int min_rt = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].rt > 0) {
                if (p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    idx = i;
                }
                 else if (p[i].rt == min_rt)
                {
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }
        if (idx != -1) {
            p[idx].rt--;
            t++;


            if (p[idx].rt == 0) {
                
                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
                completed++;
            }
        } 
        else {
 
            t++;
        }
    }
    printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i+1, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    struct process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    srtf(p, n);

    return 0;
}
