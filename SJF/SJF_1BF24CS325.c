#include <stdio.h>
#include <limits.h>

int main()
{
    int n,i,current_time=0,completed=0,idx;
    int pid[100],at[100],bt[100],ct[100],tat[100],wt[100],done[100]={0};
    float avg_tat=0,avg_wt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        pid[i]=i+1;
        printf("Enter Arrival Time and Burst Time for P%d: ",pid[i]);
        scanf("%d%d",&at[i],&bt[i]);
    }

    while(completed<n)
    {
        idx=-1;
        int min=INT_MAX;

        for(i=0;i<n;i++)
        {
            if(at[i]<=current_time && done[i]==0 && bt[i]<min)
            {
                min=bt[i];
                idx=i;
            }
        }

        if(idx==-1)
        {
            current_time++;
        }
        else
        {
            ct[idx]=current_time+bt[idx];
            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];
            current_time=ct[idx];
            done[idx]=1;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],at[i],bt[i],ct[i],tat[i],wt[i]);
        avg_tat+=tat[i];
        avg_wt+=wt[i];
    }

    avg_tat/=n;
    avg_wt/=n;

    printf("\nAverage Turnaround Time: %.2f",avg_tat);
    printf("\nAverage Waiting Time: %.2f",avg_wt);

    return 0;
}
