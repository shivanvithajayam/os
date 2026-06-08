#include<stdio.h>
#define max 10
struct process{
    int at;
    int wt;
    int ct;
    int done;
    int tat;
    int bt;
};
void sjf(struct process p[],int n){
    int completed=0;
    int t=0;
    float total_tat=0,total_wt=0;
    while(completed<n){
        int idx = -1; // Use -1 to indicate no process found
        int min_bt = 9999;
        for(int i=0;i<n;i++){
            if(p[i].at<=t && p[i].done==0){
                if(p[i].bt<min_bt){
                    min_bt = p[i].bt;
                    idx=i;
                }
            }
            else if(p[i].bt==min_bt){
                if(p[i].at<p[idx].at){
                    idx=i;
                }

            }
        }
        if(idx!=-1){
            p[idx].wt=t-p[idx].at;
            p[idx].ct=t+p[idx].bt;
            p[idx].tat=p[idx].wt+p[idx].bt;
            total_wt+=p[idx].wt;
            total_tat+=p[idx].tat;
            p[idx].done=1;
            completed++;
            t=p[idx].ct;
        }
        else
        {
            t++;
        }

    }
    printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct,p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}
int main(){
    int n;
    printf("enter num of processes");
    scanf("%d",&n);
    struct process p[max];
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &p[i].bt);
        p[i].done = 0; 
    }
    sjf(p,n);
    return 0;

}