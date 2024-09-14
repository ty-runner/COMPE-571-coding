#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	double sum = 0;
	double N = atof(argv[1]);
	for (double i = 1; i < N; i++){
		sum += i;
	}
	printf("Sum is: %.0f\n", sum);
	return 0;
}	
