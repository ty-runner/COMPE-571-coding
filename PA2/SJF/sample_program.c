#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>

/*
***********************************************************************************
*************
These DEFINE statements represent the workload size of each task and
the time quantum values for Round Robin scheduling for each task.
***********************************************************************************
**************/
#define WORKLOAD1 100000
#define WORKLOAD2 50000
#define WORKLOAD3 25000
#define WORKLOAD4 10000

/*
***********************************************************************************
*************
DO NOT CHANGE THE FUNCTION IMPLEMENTATION
***********************************************************************************
**************/
void myfunction(int param) {
    int i = 2;
    int j, k;
    while (i < param) {
        k = i; 
        for (j = 2; j <= k; j++) {
            if (k % j == 0) {
                k = k / j;
                j--;
                if (k == 1) {
                    break;
                }
            }
        }
        i++;
    }
}

/*
***********************************************************************************
*************
Struct to hold process information for SJF
***********************************************************************************
**************/
typedef struct {
    pid_t pid;
    int workload;
    long response_time; // To store response time
} Process;

int main(int argc, char const *argv[]) {
    Process processes[4];
    
    // Initialize processes with workload sizes
    processes[3] = (Process){.pid = 0, .workload = WORKLOAD1, .response_time = 0};
    processes[2] = (Process){.pid = 0, .workload = WORKLOAD2, .response_time = 0};
    processes[1] = (Process){.pid = 0, .workload = WORKLOAD3, .response_time = 0};
    processes[0] = (Process){.pid = 0, .workload = WORKLOAD4, .response_time = 0};

    // Fork processes and store their PIDs
    for (int i = 0; i < 4; i++) {
        processes[i].pid = fork();
        if (processes[i].pid == 0) {
            myfunction(processes[i].workload);
            exit(0);
        }
    }

    // Calculate response times and store them in the Process struct
    struct timeval finish_time, start_time;

    // Execute processes based on SJF scheduling
    for (int i = 0; i < 4; i++) {
        gettimeofday(&start_time, NULL); // Get start time
        kill(processes[i].pid, SIGCONT); // Continue process
        waitpid(processes[i].pid, NULL, 0); // Wait for process to finish
        gettimeofday(&finish_time, NULL); // Get finish time

        // Calculate response time
        processes[i].response_time = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec);
    }

    // Print response times
    for (int i = 0; i < 4; i++) {
        printf("Response Time for Process with Workload %d: %ld microseconds\n", processes[i].workload, processes[i].response_time);
    }

    // Calculate average response time
    long total_response_time = 0;
    for (int i = 0; i < 4; i++) {
        total_response_time += processes[i].response_time;
    }
    printf("Average response time: %ld microseconds\n", total_response_time / 4);

    return 0;
}
