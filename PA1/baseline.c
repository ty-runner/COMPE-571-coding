#include <stdio.h>
#include <stdlib.h>

unsigned long long calc_sum(unsigned long long N){
	unsigned long long sum = 0;
	for (unsigned long long i = 0; i < N; i++){
		sum+=i;
	}
	return sum;
}

int main (int argc, char *argv[]) {
	unsigned long long N = strtoull(argv[1], NULL, 10);
	unsigned long long sum = calc_sum(N);
	printf("Sum is: %llu\n", sum);
	return 0;
}	
