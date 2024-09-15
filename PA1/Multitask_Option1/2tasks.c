#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	long double N = atoi(argv[1]);
	int num_tasks = atoi(argv[2]);
	long double i = 0;
	long double chunk_size = N / num_tasks;
	int pipefd[2];
	pipe(pipefd);
	//we need to split into tasks before summing, lets start with 2 tasks, so 1 fork call
	int pid = fork();
	//if child, lets do the first half
	if(pid == 0){
		long double child_sum = 0;
		for(i = 0; i < chunk_size; i++){
			child_sum += i;
		}
		write(pipefd[1], &child_sum, sizeof(child_sum));
		close(pipefd[1]);
	}
	else{
		long double sum = 0;
		for(i = chunk_size; i < N; i++){
			sum += i;
		}
		long double child_sum;
		read(pipefd[0], &child_sum, sizeof(child_sum));
		close(pipefd[0]);
		sum += child_sum;
		printf("Sum is: %Lf\n", sum);
	}
	return 0;
}
