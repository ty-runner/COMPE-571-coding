# COMPE571 – Embedded Operating Systems – Programming Assignment 2

## Group Members:
- Ty Runner
- Tri Bui

## Assignment Overview:
This project implements and compares different scheduling algorithms using C in a UNIX environment. The implemented algorithms include:
- **Round Robin (RR)**
- **Shortest Job First (SJF)**
- **First Come First Serve (FCFS)**
- **Multi-Level Feedback Queue (MLFQ)**

The child processes perform prime factorization as their workload, and the scheduling algorithms manage process execution using UNIX signals. The performance of the algorithms is evaluated based on **average response time**.

## Files in this Project:
- **round_robin.c**: Implementation of the Round Robin scheduling algorithm.
- **sjf.c**: Implementation of the Shortest Job First scheduling algorithm.
- **fcfs.c**: Implementation of the First Come First Serve scheduling algorithm.
- **mlfq.c**: Implementation of the Multi-Level Feedback Queue scheduling algorithm.
- **Makefile**: Makefile to compile the project.
- **README.md**: This file.
- **report.pdf**: Project report explaining the implementation and results of experiments.

## Assumptions and Modifications:
1. **Round Robin**: We modified the sample Round Robin scheduling algorithm by experimenting with different time quantum values to find the optimal one.
2. **Shortest Job First (SJF)**: Assumes that we know the workload sizes in advance to prioritize shorter jobs.
3. **FCFS**: Processes are scheduled in the order they are created, with no preemption.
4. **MLFQ**: A two-level queue is implemented where the first level uses Round Robin, and the second level uses FCFS.

## Experimentation:
- **Experiment 1**: Finding the best time quantum value for Round Robin based on workload sizes.
- **Experiment 2**: Finding the best time quantum for MLFQ with different workload configurations.
- **Experiment 3a and 3b**: Comparing all algorithms using both varied and uniform workload sizes to measure performance based on average response time.
