#!/bin/bash

gcc multitask_option1.c -o multitask_option1.o

values=(100000000 1000000000 10000000000)
num_tasks=(2 4 6)

for i in {0..2}; do
	echo "Running N = ${values[$i]} and Tasks = ${num_tasks[$i]}"
	./multitask_option1.o "${values[$i]}" "${num_tasks[$i]}"
done
