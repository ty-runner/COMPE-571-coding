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
                k = k/j;
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
*************/
typedef struct {
    pid_t pid;
    int workload;
    long response_time; // To store response time
} Process;

int main(int argc, char const *argv[]) {
    // Create an array to hold the process information
    Process processes[4];
    
    // Declare process IDs and response time tracking variables
    pid_t pid1, pid2, pid3, pid4;
    struct timeval finish_time, start_time; 

    // Initialize processes using fork
    pid1 = fork();
    if (pid1 == 0) {
        myfunction(WORKLOAD1);
        exit(0);
    }
    kill(pid1, SIGSTOP); // Child process created but paused
    processes[0] = (Process){pid1, WORKLOAD1, 0}; // Store PID and workload

    pid2 = fork();
    if (pid2 == 0) {
        myfunction(WORKLOAD2);
        exit(0);
    }
    kill(pid2, SIGSTOP); // Child process created but paused
    processes[1] = (Process){pid2, WORKLOAD2, 0}; // Store PID and workload

    pid3 = fork();
    if (pid3 == 0) {
        myfunction(WORKLOAD3);
        exit(0);
    }
    kill(pid3, SIGSTOP); // Child process created but paused
    processes[2] = (Process){pid3, WORKLOAD3, 0}; // Store PID and workload

    pid4 = fork();
    if (pid4 == 0) {
        myfunction(WORKLOAD4);
        exit(0);
    }
    kill(pid4, SIGSTOP); // Child process created but paused
    processes[3] = (Process){pid4, WORKLOAD4, 0}; // Store PID and workload

    // P1 => P2 => P3 => P4
    for (int i = 0; i < 4; i++) {
        gettimeofday(&start_time, NULL); // Get start time
        kill(processes[i].pid, SIGCONT); // Continue process
        waitpid(processes[i].pid, NULL, 0); // Wait for process to finish
        gettimeofday(&finish_time, NULL); // Get finish time

        // Calculate response time
        processes[i].response_time = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec);
    }

    // Print response times
    long total_response_time = 0;
    for (int i = 0; i < 4; i++) {
        printf("Response Time for Process with Workload %d: %ld microseconds\n", processes[i].workload, processes[i].response_time);
        total_response_time += processes[i].response_time;
    }
    printf("Average response time: %ld microseconds\n", total_response_time / 4);

    return 0;
}