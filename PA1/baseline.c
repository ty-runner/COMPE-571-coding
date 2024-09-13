#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	long long sum = 0;
	int N = atoi(argv[1]);
	for (int i = 0; i < N; i++){
		sum += i;
	}
	printf("Sum is: %lld\n", sum);
	return 0;
}	
