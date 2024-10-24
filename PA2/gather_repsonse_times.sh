#!/bin/bash

# Function to compile and run a program
compile_and_run() {
    program=$1
    output_file=$2

    echo "Running $program..." >> $output_file

    # Compile the program
    gcc -o $program $program.c

    # Run the program and extract response times
    ./$program | grep "Response time" | sort >> $output_file

    # Add a newline for readability
    echo "" >> $output_file

    # Clean up
    rm $program
}

# Run the entire process 6 times
for i in {0..9}
do
    # Output file for response times
    response_times_file="response_times_$i.txt"

    # Clear the response times file if it exists
    > $response_times_file

    echo "Run $i" >> $response_times_file
    echo "======" >> $response_times_file

    # Compile and run programs in order
    compile_and_run RR $response_times_file
    compile_and_run SJF $response_times_file
    compile_and_run FCFS $response_times_file
    compile_and_run MLFQ $response_times_file

    echo "Run $i completed. Results saved to $response_times_file"
    echo ""
done

echo "All runs completed. Results saved to response_times_[0-9].txt files."