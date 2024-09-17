#!/bin/bash

gcc baseline.c -o baseline.o

values=(100000000 1000000000 10000000000)
#NUM_THREADS={2, 4, 8}
#NUM_TASKS={2, 4, 8}

for value in "${values[@]}"
do
	echo "Testing with N = $value"
	./baseline.o $value
	echo "------------------"
done
