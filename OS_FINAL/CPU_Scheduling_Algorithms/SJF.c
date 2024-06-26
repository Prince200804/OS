#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int isCompleted;
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    int completedProcesses = 0;

    printf("Gantt Chart:\n");

    while (completedProcesses < n) {
        int shortestJobIndex = -1;
        int shortestJobBurst = 9999; 

        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted) {
                if (processes[i].burstTime < shortestJobBurst) {
                    shortestJobBurst = processes[i].burstTime;
                    shortestJobIndex = i;
                }
            }
        }

        if (shortestJobIndex == -1) {
            currentTime++;
            continue;
        }

        
        printf("%d-P%d-%d ", currentTime, processes[shortestJobIndex].processID, currentTime + processes[shortestJobIndex].burstTime);

        processes[shortestJobIndex].completionTime = currentTime + processes[shortestJobIndex].burstTime;
        processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].completionTime - processes[shortestJobIndex].arrivalTime;
        processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].turnaroundTime - processes[shortestJobIndex].burstTime;
        processes[shortestJobIndex].isCompleted = 1;

        
        totalWaitingTime += processes[shortestJobIndex].waitingTime;
        totalTurnaroundTime += processes[shortestJobIndex].turnaroundTime;

        
        currentTime = processes[shortestJobIndex].completionTime;

        completedProcesses++;
    }

    printf("\n\nProcessID\tArrival-Time\tBurst-Time\tCompletion-Time\tTurnaround-Time\tWaiting-Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime,
               processes[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].isCompleted = 0;
    }
    calculateTimes(processes, n);
    return 0;
}

