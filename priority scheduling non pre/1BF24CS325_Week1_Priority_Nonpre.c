#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int process_id[n], arrival_time[n], burst_time[n], priority[n];
    int completion_time[n], turnaround_time[n], waiting_time[n];
    int completed[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        printf("  Process ID     : ");
        scanf("%d", &process_id[i]);
        printf("  Arrival Time   : ");
        scanf("%d", &arrival_time[i]);
        printf("  Burst Time     : ");
        scanf("%d", &burst_time[i]);
        printf("  Priority       : ");
        scanf("%d", &priority[i]);
        completed[i] = 0;
    }

    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n) {
        int highest_priority = 99999;
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && completed[i] == 0) {
                if (priority[i] < highest_priority) {
                    highest_priority = priority[i];
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            current_time++;
        } else {
            completion_time[selected]  = current_time + burst_time[selected];
            turnaround_time[selected]  = completion_time[selected] - arrival_time[selected];
            waiting_time[selected]     = turnaround_time[selected] - burst_time[selected];
            current_time               = completion_time[selected];
            completed[selected]        = 1;
            completed_count++;
        }
    }

    // Calculate averages
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt  += waiting_time[i];
        total_tat += turnaround_time[i];
    }

    // Print results table
    printf("\n+-----+--------+-------+----------+------------+-----------------+--------------+\n");
    printf("| PID |   AT   |  BT   | Priority |    CT      |       TAT       |      WT      |\n");
    printf("+-----+--------+-------+----------+------------+-----------------+--------------+\n");

    for (int i = 0; i < n; i++) {
        printf("|  %2d |   %3d  |  %3d  |    %3d   |     %3d    |       %3d       |      %3d     |\n",
               process_id[i], arrival_time[i], burst_time[i],
               priority[i], completion_time[i],
               turnaround_time[i], waiting_time[i]);
    }

    printf("+-----+--------+-------+----------+------------+-----------------+--------------+\n");
    printf("\nAverage Turnaround Time : %.2f", total_tat / n);
    printf("\nAverage Waiting Time    : %.2f\n", total_wt  / n);

    return 0;
}
