#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // First fork
    if ((pid = fork()) == 0) {
        // Second fork
        if ((pid = fork()) == 0) {
            // Grandchild process
            printf("3\n");
        } else {
            // Child process
            wait(NULL);  // Wait for the grandchild to finish
            printf("4\n");
        }
    } else {
        // Parent process
        if ((pid = fork()) == 0) {
            // Child process of the parent
            printf("1\n");
            exit(0);  // Ensure this child exits after printing
        }
        printf("2\n");
        wait(NULL);  // Wait for the child to finish
    }
    
    printf("0\n");
    return 0;
}
