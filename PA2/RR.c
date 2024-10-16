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

#define QUANTUM1 5000
#define QUANTUM2 5000
#define QUANTUM3 5000
#define QUANTUM4 5000

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
int main(int argc, char const *argv[]) {
    pid_t pid1, pid2, pid3, pid4;
    int running1, running2, running3, running4;
    
    struct timeval finish_time, start_time1, start_time2, start_time3, start_time4; // For response time tracking
    long response_time1, response_time2, response_time3, response_time4;

    pid1 = fork();
    if (pid1 == 0) {
        myfunction(WORKLOAD1);
        exit(0);
    }
    kill(pid1, SIGSTOP); // child process created but paused

    pid2 = fork();
    if (pid2 == 0) {
        myfunction(WORKLOAD2);
        exit(0);
    }
    kill(pid2, SIGSTOP); // child process created but paused

    pid3 = fork();
    if (pid3 == 0) {
        myfunction(WORKLOAD3);
        exit(0);
    }
    kill(pid3, SIGSTOP); // child process created but paused

    pid4 = fork();
    if (pid4 == 0) {
        myfunction(WORKLOAD4);
        exit(0);
    }
    kill(pid4, SIGSTOP); // child process created but paused
/**********************************************************************************
**************
At this point, all newly-created child processes are stopped, and
ready for scheduling.
***********************************************************************************
**************/
/**********************************************************************************
**************
- Scheduling code starts here
- Below is a sample schedule. (which scheduling algorithm is this?)
- For the assignment purposes, you have to replace this part with the
other scheduling methods
to be implemented.
***********************************************************************************
*************/
    running1 = 1;
    running2 = 1;
    running3 = 1;
    running4 = 1;
    // Initialize response time tracking variables
    int first_run1 = 0, first_run2 = 0, first_run3 = 0, first_run4 = 0;

    while (running1 > 0 || running2 > 0 || running3 > 0 || running4 > 0) {
        if (running1 > 0) {
            if (!first_run1) { // If this is the first run for pid1
                gettimeofday(&start_time1, NULL); // Get start time
                first_run1 = 1; // Mark that we have started running this process
            }
            kill(pid1, SIGCONT); // Continue process 1
            usleep(QUANTUM1); // Process 1 runs for QUANTUM1 microseconds
            kill(pid1, SIGSTOP); // Stop process 1
        }
        if (running2 > 0) {
            if (!first_run2) { // If this is the first run for pid2
                gettimeofday(&start_time2, NULL); // Get start time
                first_run2 = 1; // Mark that we have started running this process
            }
            kill(pid2, SIGCONT); // Continue process 2
            usleep(QUANTUM2); // Process 2 runs for QUANTUM2 microseconds
            kill(pid2, SIGSTOP); // Stop process 2
        }
        if (running3 > 0) {
            if (!first_run3) { // If this is the first run for pid3
                gettimeofday(&start_time3, NULL); // Get start time
                first_run3 = 1; // Mark that we have started running this process
            }
            kill(pid3, SIGCONT); // Continue process 3
            usleep(QUANTUM3); // Process 3 runs for QUANTUM3 microseconds
            kill(pid3, SIGSTOP); // Stop process 3
        }
        if (running4 > 0) {
            if (!first_run4) { // If this is the first run for pid4
                gettimeofday(&start_time4, NULL); // Get start time
                first_run4 = 1; // Mark that we have started running this process
            }
            kill(pid4, SIGCONT); // Continue process 4
            usleep(QUANTUM4); // Process 4 runs for QUANTUM4 microseconds
            kill(pid4, SIGSTOP); // Stop process 4
        }
        
        if(waitpid(pid1, &running1, WNOHANG) > 0){
            gettimeofday(&finish_time, NULL);
            response_time1 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time1.tv_sec * 1000000 + start_time1.tv_usec);
	    }	
        if(waitpid(pid2, &running2, WNOHANG) > 0){
            gettimeofday(&finish_time, NULL);
            response_time2 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time2.tv_sec * 1000000 + start_time2.tv_usec);
	    }
        if(waitpid(pid3, &running3, WNOHANG) > 0){
            gettimeofday(&finish_time, NULL);
            response_time3 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time3.tv_sec * 1000000 + start_time3.tv_usec);
	    }
        if(waitpid(pid4, &running4, WNOHANG) > 0){
            gettimeofday(&finish_time, NULL);
            response_time4 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time4.tv_sec * 1000000 + start_time4.tv_usec);
	    }
    }

    // Calculate response times
    printf("Response Time for Process 1: %ld microseconds\n", response_time1);
    printf("Response Time for Process 2: %ld microseconds\n", response_time2);
    printf("Response Time for Process 3: %ld microseconds\n", response_time3);
    printf("Response Time for Process 4: %ld microseconds\n", response_time4);
    printf("Average response time: %ld microseconds\n", (response_time1 + response_time2 + response_time3 + response_time4) / 4);
    
/**********************************************************************************
**************
- Scheduling code ends here
***********************************************************************************
*************/

    return 0;
}
