#include <stdio.h>

int main()
{
    int n, time_quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    int process_id[n], arrival_time[n], burst_time[n];
    int remaining_time[n], waiting_time[n], turnaround_time[n];
    int completed[n], in_queue[n];

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arrival_time[i]);
        process_id[i]    = i + 1;
        remaining_time[i] = 0;
        waiting_time[i]   = 0;
        turnaround_time[i] = 0;
        completed[i]      = 0;
        in_queue[i]       = 0;
    }

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    // Queue implemented as array
    int queue[1000], front = 0, rear = 0;

    int current_time    = 0;
    int completed_count = 0;

    // Add processes arriving at time 0
    for (int i = 0; i < n; i++)
    {
        if (arrival_time[i] <= current_time && !in_queue[i])
        {
            queue[rear++] = i;
            in_queue[i]   = 1;
        }
    }

    while (completed_count < n)
    {
        // CPU idle
        if (front == rear)
        {
            current_time++;
            for (int i = 0; i < n; i++)
            {
                if (arrival_time[i] <= current_time && !in_queue[i] && !completed[i])
                {
                    queue[rear++] = i;
                    in_queue[i]   = 1;
                }
            }
            continue;
        }

        int p = queue[front++];

        if (remaining_time[p] > time_quantum)
        {
            current_time      += time_quantum;
            remaining_time[p] -= time_quantum;

            for (int i = 0; i < n; i++)
            {
                if (arrival_time[i] <= current_time && !in_queue[i] && !completed[i])
                {
                    queue[rear++] = i;
                    in_queue[i]   = 1;
                }
            }

            queue[rear++] = p;
        }
        else
        {
            current_time      += remaining_time[p];
            remaining_time[p]  = 0;

            turnaround_time[p] = current_time - arrival_time[p];
            waiting_time[p]    = turnaround_time[p] - burst_time[p];

            completed[p]       = 1;
            completed_count++;

            for (int i = 0; i < n; i++)
            {
                if (arrival_time[i] <= current_time && !in_queue[i] && !completed[i])
                {
                    queue[rear++] = i;
                    in_queue[i]   = 1;
                }
            }
        }
    }

    // Remaining time after completion = 0 for all
    for (int i = 0; i < n; i++)
        remaining_time[i] = 0;

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += turnaround_time[i];
        avg_wt  += waiting_time[i];
    }

    // Print table
    printf("\nRRS scheduling:\n");
    printf("%-5s%-5s%-5s%-5s%-5s%-5s%-5s\n",
           "PID", "AT", "BT", "CT", "TAT", "WT", "RT");

    for (int i = 0; i < n; i++)
    {
        int ct = arrival_time[i] + turnaround_time[i];
        printf("%-5d%-5d%-5d%-5d%-5d%-5d%-5d\n",
               process_id[i], arrival_time[i], burst_time[i],
               ct, turnaround_time[i], waiting_time[i], remaining_time[i]);
    }

    printf("\nAverage turnaround time:%.6fms", avg_tat / n);
    printf("\nAverage waiting time:%.6fms\n",  avg_wt  / n);

    return 0;
}
