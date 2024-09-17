#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long calc_sum(unsigned long long N) {
    unsigned long long sum = 0;
    for (unsigned long long i = 0; i < N; i++) {
        sum += i;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    unsigned long long N = strtoull(argv[1], NULL, 10);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    unsigned long long sum = calc_sum(N);

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Sum is: %llu\n", sum);
    printf("Elapsed time: %.6f seconds\n", elapsed_time);

    return 0;
}
