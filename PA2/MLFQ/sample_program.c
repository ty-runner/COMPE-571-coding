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
* These DEFINE statements represent the workload size of each task and
* the time quantum values for each queue in MLFQ.
***********************************************************************************/
#define WORKLOAD1 100000
#define WORKLOAD2 50000
#define WORKLOAD3 25000
#define WORKLOAD4 10000

#define QUANTUM1 5000
#define QUANTUM2 10000
#define QUANTUM3 15000

/*
***********************************************************************************
* DO NOT CHANGE THE FUNCTION IMPLEMENTATION
***********************************************************************************/
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
    
    struct timeval finish_time, start_time1, start_time2, start_time3, start_time4;
    long response_time1 = 0, response_time2 = 0, response_time3 = 0, response_time4 = 0;

    // Fork processes
    pid1 = fork();
    if (pid1 == 0) {
        myfunction(WORKLOAD1);
        exit(0);
    }
    kill(pid1, SIGSTOP);

    pid2 = fork();
    if (pid2 == 0) {
        myfunction(WORKLOAD2);
        exit(0);
    }
    kill(pid2, SIGSTOP);

    pid3 = fork();
    if (pid3 == 0) {
        myfunction(WORKLOAD3);
        exit(0);
    }
    kill(pid3, SIGSTOP);

    pid4 = fork();
    if (pid4 == 0) {
        myfunction(WORKLOAD4);
        exit(0);
    }
    kill(pid4, SIGSTOP);
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
    // Initialize response time tracking variables
    int first_run1 = 0, first_run2 = 0, first_run3 = 0, first_run4 = 0;

    // Queue system for MLFQ
    int queue1[] = {pid1, pid2, pid3, pid4};
    int queue2[4], queue3[4];
    int q1_size = 4, q2_size = 0, q3_size = 0;

    while (q1_size > 0 || q2_size > 0 || q3_size > 0) {
        // Round Robin on Queue 1
        for (int i = 0; i < q1_size; i++) {
            if (!first_run1 && queue1[i] == pid1) {
                gettimeofday(&start_time1, NULL);
                first_run1 = 1;
            } else if (!first_run2 && queue1[i] == pid2) {
                gettimeofday(&start_time2, NULL);
                first_run2 = 1;
            } else if (!first_run3 && queue1[i] == pid3) {
                gettimeofday(&start_time3, NULL);
                first_run3 = 1;
            } else if (!first_run4 && queue1[i] == pid4) {
                gettimeofday(&start_time4, NULL);
                first_run4 = 1;
            }

            kill(queue1[i], SIGCONT);
            usleep(QUANTUM1); // Run for QUANTUM1 time
            kill(queue1[i], SIGSTOP);

            if (waitpid(queue1[i], &running1, WNOHANG) > 0) {
                if (queue1[i] == pid1) {
                    gettimeofday(&finish_time, NULL);
                    response_time1 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time1.tv_sec * 1000000 + start_time1.tv_usec);
                } else if (queue1[i] == pid2) {
                    gettimeofday(&finish_time, NULL);
                    response_time2 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time2.tv_sec * 1000000 + start_time2.tv_usec);
                } else if (queue1[i] == pid3) {
                    gettimeofday(&finish_time, NULL);
                    response_time3 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time3.tv_sec * 1000000 + start_time3.tv_usec);
                } else if (queue1[i] == pid4) {
                    gettimeofday(&finish_time, NULL);
                    response_time4 = (finish_time.tv_sec * 1000000 + finish_time.tv_usec) - (start_time4.tv_sec * 1000000 + start_time4.tv_usec);
                }
                // Process finished, remove from Queue 1
                for (int j = i; j < q1_size - 1; j++) {
                    queue1[j] = queue1[j + 1];
                }
                q1_size--;
                i--;
            } else {
                // Move to Queue 2
                queue2[q2_size++] = queue1[i];
                for (int j = i; j < q1_size - 1; j++) {
                    queue1[j] = queue1[j + 1];
                }
                q1_size--;
                i--;
            }
        }

        // Round Robin on Queue 2
        for (int i = 0; i < q2_size; i++) {
            kill(queue2[i], SIGCONT);
            usleep(QUANTUM2);
            kill(queue2[i], SIGSTOP);

            if (waitpid(queue2[i], &running2, WNOHANG) > 0) {
                if (queue2[i] == pid1 || queue2[i] == pid2 || queue2[i] == pid3 || queue2[i] == pid4) {
                    // Process finished, no need to track more
                }
                for (int j = i; j < q2_size - 1; j++) {
                    queue2[j] = queue2[j + 1];
                }
                q2_size--;
                i--;
            } else {
                // Move to Queue 3
                queue3[q3_size++] = queue2[i];
                for (int j = i; j < q2_size - 1; j++) {
                    queue2[j] = queue2[j + 1];
                }
                q2_size--;
                i--;
            }
        }

        // Round Robin on Queue 3
        for (int i = 0; i < q3_size; i++) {
            kill(queue3[i], SIGCONT);
            usleep(QUANTUM3);
            kill(queue3[i], SIGSTOP);

            if (waitpid(queue3[i], &running3, WNOHANG) > 0) {
                if (queue3[i] == pid1 || queue3[i] == pid2 || queue3[i] == pid3 || queue3[i] == pid4) {
                    // Process finished, no need to track more
                }
                for (int j = i; j < q3_size - 1; j++) {
                    queue3[j] = queue3[j + 1];
                }
                q3_size--;
                i--;
            }
        }
    }

    // Output response times
    printf("Response Time for Process 1: %ld microseconds\n", response_time1);
    printf("Response Time for Process 2: %ld microseconds\n", response_time2);
    printf("Response Time for Process 3: %ld microseconds\n", response_time3);
    printf("Response Time for Process 4: %ld microseconds\n", response_time4);
    printf("Average response time: %ld microseconds\n", (response_time1 + response_time2 + response_time3 + response_time4) / 4);

    return 0;
}
