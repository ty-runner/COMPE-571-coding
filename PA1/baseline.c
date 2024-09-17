#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long double calc_sum(long double N) {
    long double sum = 0;
    for (long double i = 0; i < N; i++) {
        sum += i;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    long double N = strtold(argv[1], NULL);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    long double sum = calc_sum(N);

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Sum is: %Lf\n", sum);
    printf("Elapsed time: %.6f seconds\n", elapsed_time);

    return 0;
}
