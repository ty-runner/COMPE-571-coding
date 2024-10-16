# Multilevel Feedback Queue
With this scheduling algorithm, we have 2 levels of queues.
## Entry Queue (Round Robin)
- This is the queue that every process will enter at the start. We need to determine the optimal quantum for this round robin.
- Ideally with the Q value, at least 1 process finishes in the round robin.
## Finisher Queue (FCFS)
- This queue is just FCFS where the first process to reach this queue gets fully executed once all processes are out of the entry queue. 
