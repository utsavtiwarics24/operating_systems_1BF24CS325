#include <stdio.h>

int main()
{
    int n, i, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], pr[n];
    int ct[n], tat[n], wt[n];


    for(i = 0; i < n; i++)
    {
        printf("\nEnter AT, BT and Priority for P%d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    int min_pr, index;

    while(completed != n)
    {
        min_pr = 9999;
        index = -1;


        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(pr[i] < min_pr)
                {
                    min_pr = pr[i];
                    index = i;
                }
            }
        }

        if(index != -1)
        {
            rt[index]--;
            time++;

            if(rt[index] == 0)
            {
                completed++;
                ct[index] = time;
            }
        }
        else
        {
            time++;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}
