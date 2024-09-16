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
    clock_gettime(CLOCK_MONOTONIC, &start_time);  // Use CLOCK_MONOTONIC for high precision

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
        close(pipes[i][1]);  // Close write end of the pipe
        read(pipes[i][0], &child_sum, sizeof(child_sum));  // Read the result from the pipe
        close(pipes[i][0]);  // Close read end of the pipe
        total_sum += child_sum;
    }

    // Stop timing
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    // Print the total sum
    printf("Total sum is: %Lf\n", total_sum);

    // Calculate and print the elapsed time
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("Elapsed time: %.6f seconds\n", elapsed_time);

    return 0;
}
