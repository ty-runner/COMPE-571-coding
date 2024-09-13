#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) {
	long long sum = 0;
	time_t start, end;
	time(&start);
	for (int i = 0; i < atoi(argv[1]); i++){
		sum += i;
	}
	time(&end);
	double time_taken = (double)(end - start);
	printf("Sum is: %lld\n", sum);
	printf("Time taken is %lf\n", time_taken);
	return 0;
}	
