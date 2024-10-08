#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Function to calculate sum for each task and send it via pipe
void calculate_sum(long double start, long double end, int pipe_fd[2]){
    long double sum = 0;
    for(long double i = start; i < end; i++){
        sum += i;
    }
    //send thru pipe
    close(pipe_fd[0]);
    write(pipe_fd[1], &sum, sizeof(sum));
    close(pipe_fd[1]);
    exit(0); //terminate child process
}

int main(int argc, char *argv[]){
    // Start timing
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    long double N = strtold(argv[1], NULL);
    int num_tasks = atoi(argv[2]);
    long double chunk_size = N / num_tasks;
    int pipes[num_tasks][2];
    pid_t pids[num_tasks];

    for(int i = 0; i < num_tasks; i++){
        pipe(pipes[i]);
        pids[i] = fork();
        if(pids[i] == 0) {

            calculate_sum(i * chunk_size, (i + 1) * chunk_size, pipes[i]);
        }
    }

    long double total_sum = 0;
    for(int i = 0; i < num_tasks; i++){
        waitpid(pids[i], NULL, 0);
        long double child_sum;
        close(pipes[i][1]);  // Close write
        read(pipes[i][0], &child_sum, sizeof(child_sum));  // Read result
        close(pipes[i][0]);  // Close read
        total_sum += child_sum;
    }

    // Stop timing
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    printf("Total sum is: %.0Lf\n", total_sum);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("Elapsed time: %.5f seconds\n", elapsed_time);

    return 0;
}
