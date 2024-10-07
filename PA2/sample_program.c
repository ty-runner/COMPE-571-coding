#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>

/************************************************************************************************ 
		These DEFINE statements represent the workload size of each task and 
		the time quantum values for Round Robin scheduling for each task.
*************************************************************************************************/

#define WORKLOAD1 100000
#define WORKLOAD2 50000
#define WORKLOAD3 25000
#define WORKLOAD4 10000

#define QUANTUM1 1000
#define QUANTUM2 1000
#define QUANTUM3 1000
#define QUANTUM4 1000

/************************************************************************************************ 
					DO NOT CHANGE THE FUNCTION IMPLEMENTATION
*************************************************************************************************/
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
/************************************************************************************************/

int main(int argc, char const *argv[]) {
	pid_t pid1, pid2, pid3, pid4;
	int running1, running2, running3, running4;
	struct timeval startTime1, startTime2, startTime3, startTime4; // To store start times
	long responseTime1, responseTime2, responseTime3, responseTime4; // To store response times
	int firstRun1 = 1, firstRun2 = 1, firstRun3 = 1, firstRun4 = 1; // Flags to track first run

	pid1 = fork();
	if (pid1 == 0) {
		myfunction(WORKLOAD1);
		exit(0);
	}
	kill(pid1, SIGSTOP); // Child process created but paused

	pid2 = fork();
	if (pid2 == 0) {
		myfunction(WORKLOAD2);
		exit(0);
	}
	kill(pid2, SIGSTOP); // Child process created but paused

	pid3 = fork();
	if (pid3 == 0) {
		myfunction(WORKLOAD3);
		exit(0);
	}
	kill(pid3, SIGSTOP); // Child process created but paused

	pid4 = fork();
	if (pid4 == 0) {
		myfunction(WORKLOAD4);
		exit(0);
	}
	kill(pid4, SIGSTOP); // Child process created but paused

	/************************************************************************************************ 
		At this point, all newly-created child processes are stopped and ready for scheduling.
	************************************************************************************************/

	/************************************************************************************************
		- Scheduling code starts here
		- This implementation uses Round Robin scheduling.
		- For the assignment purposes, you have to replace this part with other scheduling methods 
		to be implemented.
	************************************************************************************************/

	running1 = 1; // Set initial state of process 1 as running
	running2 = 1; // Set initial state of process 2 as running
	running3 = 1; // Set initial state of process 3 as running
	running4 = 1; // Set initial state of process 4 as running

	while (running1 > 0 || running2 > 0 || running3 > 0 || running4 > 0) {
		if (running1 > 0) {
			if (firstRun1) {
				gettimeofday(&startTime1, NULL); // Record start time for process 1
				firstRun1 = 0; // Mark that process 1 has been started
			}
			kill(pid1, SIGCONT); // Continue process 1
			usleep(QUANTUM1);    // Process 1 runs for QUANTUM1 microseconds
			kill(pid1, SIGSTOP); // Stop process 1
		}
		if (running2 > 0) {
			if (firstRun2) {
				gettimeofday(&startTime2, NULL); // Record start time for process 2
				firstRun2 = 0; // Mark that process 2 has been started
			}
			kill(pid2, SIGCONT); // Continue process 2
			usleep(QUANTUM2);    // Process 2 runs for QUANTUM2 microseconds
			kill(pid2, SIGSTOP); // Stop process 2
		}
		if (running3 > 0) {
			if (firstRun3) {
				gettimeofday(&startTime3, NULL); // Record start time for process 3
				firstRun3 = 0; // Mark that process 3 has been started
			}
			kill(pid3, SIGCONT); // Continue process 3
			usleep(QUANTUM3);    // Process 3 runs for QUANTUM3 microseconds
			kill(pid3, SIGSTOP); // Stop process 3
		}
		if (running4 > 0) {
			if (firstRun4) {
				gettimeofday(&startTime4, NULL); // Record start time for process 4
				firstRun4 = 0; // Mark that process 4 has been started
			}
			kill(pid4, SIGCONT); // Continue process 4
			usleep(QUANTUM4);    // Process 4 runs for QUANTUM4 microseconds
			kill(pid4, SIGSTOP); // Stop process 4
		}

		waitpid(pid1, &running1, WNOHANG); // Check if process 1 has finished
		waitpid(pid2, &running2, WNOHANG); // Check if process 2 has finished
		waitpid(pid3, &running3, WNOHANG); // Check if process 3 has finished
		waitpid(pid4, &running4, WNOHANG); // Check if process 4 has finished
	}

	// Calculate and print response times after all processes are done
	gettimeofday(&startTime1, NULL);
	responseTime1 = (startTime1.tv_sec - startTime1.tv_sec) * 1000000 + (startTime1.tv_usec - startTime1.tv_usec);
	printf("Response time for Process 1: %ld microseconds\n", responseTime1);

	gettimeofday(&startTime2, NULL);
	responseTime2 = (startTime2.tv_sec - startTime2.tv_sec) * 1000000 + (startTime2.tv_usec - startTime2.tv_usec);
	printf("Response time for Process 2: %ld microseconds\n", responseTime2);

	gettimeofday(&startTime3, NULL);
	responseTime3 = (startTime3.tv_sec - startTime3.tv_sec) * 1000000 + (startTime3.tv_usec - startTime3.tv_usec);
	printf("Response time for Process 3: %ld microseconds\n", responseTime3);

	gettimeofday(&startTime4, NULL);
	responseTime4 = (startTime4.tv_sec - startTime4.tv_sec) * 1000000 + (startTime4.tv_usec - startTime4.tv_usec);
	printf("Response time for Process 4: %ld microseconds\n", responseTime4);

	/************************************************************************************************
		- Scheduling code ends here
	************************************************************************************************/

	return 0;
}
