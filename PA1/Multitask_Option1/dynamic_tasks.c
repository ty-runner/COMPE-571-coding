#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void calculate_sum(long double start, long double end, long double pipe_fd[2]){
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
    long double N = strtold(argv[1], NULL);
    int num_tasks = atoi(argv[2]);
    long double chunk_size = N / num_tasks;
    long double pipes[num_tasks][2];
    pid_t pids[num_tasks];

    for(int i = 0; i < num_tasks; i++){
        pipe(pipes[i]);
        pids[i] = fork();
        if(pids[i] == 0){

            calculate_sum(i * chunk_size, (i + 1) * chunk_size, pipes[i]);
        }
    }

    long double total_sum = 0;
    for(int i = 0; i < num_tasks; i++){
        waitpid(pids[i], NULL, 0);
        long double child_sum;
        close(pipes[i][1]);
        read(pipes[i][0], &child_sum, sizeof(child_sum));
        close(pipes[i][0]);
        total_sum += child_sum;
    }
    printf("Total sum is: %Lf\n", total_sum);
    return 0;
}