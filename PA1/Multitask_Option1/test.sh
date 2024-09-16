#!/bin/bash

gcc dynamic_tasks.c -o dynamic.o

values=(100000000 1000000000 10000000000)
num_tasks=(2 4 8)

for i in {0..2}; do
	echo "Running N = ${values[$i]} and Tasks = ${num_tasks[$i]}"
	./dynamic.o "${values[$i]}" "${num_tasks[$i]}"
done
