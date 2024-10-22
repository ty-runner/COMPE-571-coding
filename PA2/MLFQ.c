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

#define QUANTUM 5000

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
    int queue1_count = 4; //initial count of the RR queue
    int queue2_count = 0; // Initial coutn fo the FCFS queue

    pid_t rr_queue[4];
    pid_t fcfs_queue[4];
    
    struct timeval start_time[4];
    struct timeval finish_time;
    long response_times[4];

    pid1 = fork();
    if (pid1 == 0) {
        myfunction(WORKLOAD1);
        exit(0);
    }
    kill(pid1, SIGSTOP); // child process created but paused
    rr_queue[0] = pid1;

    pid2 = fork();
    if (pid2 == 0) {
        myfunction(WORKLOAD2);
        exit(0);
    }
    kill(pid2, SIGSTOP); // child process created but paused
    rr_queue[1] = pid2;

    pid3 = fork();
    if (pid3 == 0) {
        myfunction(WORKLOAD3);
        exit(0);
    }
    kill(pid3, SIGSTOP); // child process created but paused
    rr_queue[2] = pid3;

    pid4 = fork();
    if (pid4 == 0) {
        myfunction(WORKLOAD4);
        exit(0);
    }
    kill(pid4, SIGSTOP); // child process created but paused
    rr_queue[3] = pid4;
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
    
    int running[4] = {0};
    int first_run[4] = {0};

    while(queue1_count > 0 || queue2_count > 0){
        //rr
        for(int i = 0; i < 4; i++){
            if(rr_queue[i] != 0){
                if(!running[i]){ //if the process isnt complete
                    if(!first_run[i]){
                        gettimeofday(&start_time[i], NULL); //start time for the process
                        first_run[i] = 1;
                    }
                    kill(rr_queue[i], SIGCONT); // Start process
                    usleep(QUANTUM); // Process runs for QUANTUM microseconds
                    kill(rr_queue[i], SIGSTOP); // Stop process
                    if(waitpid(rr_queue[i], &running[i], WNOHANG) > 0){ //process finished!
                        gettimeofday(&finish_time, NULL);
                        response_times[i] = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time[i].tv_sec * 1000000 + start_time[i].tv_usec);
                        printf("Response Time for Process %d: %ld microseconds\n", i, response_times[i]);
                    }
                    else{ //if the process didn't finish, ship it to the FCFS queue
                        fcfs_queue[queue2_count++] = rr_queue[i];
                        rr_queue[i] = 0;
                        queue1_count--;
                    }
                }
            }
        }
        //fcfs
        if(queue1_count == 0 && queue2_count > 0){
            for(int i = 0; i < queue2_count; i++){
                if(fcfs_queue[i] != 0){
                    kill(fcfs_queue[i], SIGCONT); // Start process
                    waitpid(fcfs_queue[i], NULL, 0);
                    gettimeofday(&finish_time, NULL);
                    response_times[i] = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time[i].tv_sec * 1000000 + start_time[i].tv_usec);
                    printf("Response Time for Process %d: %ld microseconds\n", i, response_times[i]);
                    fcfs_queue[i] = 0;
                }
            }
            queue2_count = 0;
        }

    }

    // Calculate response times
    printf("Average response time: %ld microseconds\n", (response_times[0] + response_times[1] + response_times[2] + response_times[3]) / 4);
    
/**********************************************************************************
**************
- Scheduling code ends here
***********************************************************************************
*************/

    return 0;
}
