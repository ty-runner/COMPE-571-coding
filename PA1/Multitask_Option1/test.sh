#!/bin/bash

gcc dynamic_tasks.c -o dynamic.o

values=(100000000 1000000000 10000000000)
num_tasks=(2 4 8)

for N in "${values[@]}"; do
    for tasks in "${num_tasks[@]}"; do
        echo "Running N = $N and Tasks = $tasks"
        ./dynamic.o "$N" "$tasks"
    done
done
