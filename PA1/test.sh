#!/bin/bash

gcc baseline.c -o baseline.o

values=(100000000 1000000000 10000000000)
#threads

for value in "${values[@]}"
do
	echo "Testing with N = $value"
	time ./baseline.o $value
	echo "------------------"
done
