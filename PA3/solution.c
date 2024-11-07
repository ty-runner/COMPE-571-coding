#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_input_file(char *input_file, int *num_tasks, int *run_time, int **tasks, int **power_levels);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <schedule> [<mode>]\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *schedule = argv[2];
    char *mode = NULL;
    int num_tasks, run_time;
    int *tasks = NULL, *power_levels = NULL;
    // if (argc == 4) { // Check if energy-efficient mode is specified
    //     mode = argv[3];
    //     if (strcmp(schedule, "EE") == 0 || strcmp(mode, "EE") == 0) {
    //         printf("Energy efficient mode enabled with schedule type: %s\n", schedule);
    //         parse_input_file(input_file, &num_tasks, &run_time, &tasks, &power_levels);
    //         return 0;
    //     }
    // }

    printf("Schedule type: %s\n", schedule);
    parse_input_file(input_file, &num_tasks, &run_time, &tasks, &power_levels);
    printf("Number of tasks: %d\n", num_tasks);
    printf("Run time: %d\n", run_time);

    printf("Tasks: ");
    for (int i = 0; i < num_tasks; i++) {
        printf("%d ", tasks[i]);
    }
    printf("\n");

    printf("Power levels: ");
    for (int i = 0; i < num_tasks; i++) {
        printf("%d ", power_levels[i]);
    }
    printf("\n");
    return 0;
}

void parse_input_file(char *input_file, int *num_tasks, int *run_time, int **tasks, int **power_levels) {
    char line[256];
    char *token;
    FILE *file = fopen(input_file, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", input_file);
        return;
    }

    // Parse the first line
    if (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, " ");
        *num_tasks = atoi(token);

        token = strtok(NULL, " ");
        *run_time = atoi(token);

        *power_levels = (int *)malloc(*num_tasks * sizeof(int));
        for (int i = 0; i < *num_tasks; i++) {
            token = strtok(NULL, " ");
            (*power_levels)[i] = atoi(token);
        }
    }

    // Parse the subsequent lines
    *tasks = (int *)malloc((*num_tasks) * sizeof(int));
    int task_index = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, " ");
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, " ");
        }
        task_index++;
    }

    fclose(file);
}