    #include<stdio.h>
    #define MAX 100
    struct process{
        int id;
        int at;
        int wt;
        int ct;
        int bt;
        int tat;
        int queue;
        int done;
    };
    void sortbyarrival(struct process p[] ,int n){
        for(int i=0;i<n-1;i++){         
            for (int j = 0; j < n - 1 - i; j++)
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
    void runFCFS(struct process p[], int n, int *currentTime)
    {
        for (int i = 0; i < n; i++)
        {
            if (*currentTime < p[i].at)
            *currentTime = p[i].at;
            p[i].wt = *currentTime - p[i].at;
            p[i].ct = *currentTime + p[i].bt;
            p[i].tat = p[i].ct - p[i].at;
            *currentTime = p[i].ct;
            p[i].done = 1;
        }
    } 
    // Function to print Gantt Chart
    void printGanttChart(struct process q[], int count, int startTime)
    {
        printf("\nGantt Chart:\n");
        printf("-------------------------------------------------\n|");

        for(int i = 0; i < count; i++)
            printf("  P%d  |", q[i].id);

        printf("\n-------------------------------------------------\n");

        printf("%d", startTime);

        for(int i = 0; i < count; i++)
            printf("     %d", q[i].ct);

        printf("\n");
    }
    int main() {
        int n;
        struct process all[MAX], systemQueue[MAX], userQueue[MAX];
        int sysCount = 0, userCount = 0;
        printf("Enter number of processes: ");
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            all[i].id = i;
            printf("\nProcess %d\n", i);

            printf("Enter arrival time: ");
            scanf("%d", &all[i].at);

            printf("Enter burst time: ");
            scanf("%d", &all[i].bt);

            printf("Enter type (0 = System, 1 = User): ");
            scanf("%d", &all[i].queue);

            all[i].done = 0;

            if (all[i].queue == 0) {
                systemQueue[sysCount++] = all[i];
            } else {
                userQueue[userCount++] = all[i];
            }
        }
        sortbyarrival(systemQueue, sysCount);
        sortbyarrival(userQueue, userCount);
        int currentTime = 0;
        runFCFS(systemQueue, sysCount, &currentTime);
        runFCFS(userQueue, userCount, &currentTime);
        for (int i = 0; i < sysCount; i++) {
            all[systemQueue[i].id] = systemQueue[i];
        }
        for (int i = 0; i < userCount; i++) {
            all[userQueue[i].id] = userQueue[i];
        }
        printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");
        float totalWT = 0, totalTAT = 0;
        for (int i = 0; i < n; i++) {
            printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
                all[i].id,
                all[i].queue == 0 ? "System" : "User",
                all[i].at, all[i].bt, all[i].ct, all[i].wt, all[i].tat);

            totalWT += all[i].wt;
            totalTAT += all[i].tat;
        }
        printf("\nAverage Waiting Time: %.2f", totalWT / n);
        printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
        printGanttChart(systemQueue, sysCount, 0);
        printGanttChart(userQueue, userCount, systemQueue[sysCount-1].ct);

        return 0;
        }

        