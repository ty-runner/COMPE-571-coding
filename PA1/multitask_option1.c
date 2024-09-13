#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	long long sum = 0;
	int N = atoi(argv[1]);
	int num_tasks = atoi(argv[2]);
	int i = 0;
	//we need to split into tasks before summing, lets start with 2 tasks, so 1 fork call
	int pid = fork();
	//if child, lets do the first half
	if(pid == 0){
		long long child_sum = 0;
		for(i = 0; i < N / 2; i++){
			child_sum += i;
		}
		sum += child_sum;
	}
	else{
		for(i = N / 2; i < N; i++){
			sum += i;
		}
		printf("Sum is: %lld\n", sum);
	}
	return 0;
}
