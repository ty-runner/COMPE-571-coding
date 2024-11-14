import copy
import sys
import math


def parse_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Parse the first line (system settings)
    first_line = lines[0].strip().split()
    num_tasks = int(first_line[0])
    system_execution_time = int(first_line[1])
    cpu_powers = {
        "1188 Mhz": int(first_line[2]),
        "918 Mhz": int(first_line[3]),
        "648 Mhz": int(first_line[4]),
        "384 Mhz": int(first_line[5]),
        "Idle": int(first_line[6])
    }

    # Parse the subsequent lines (task data)
    tasks = []
    for line in lines[1:num_tasks + 1]:  # Loop through the number of tasks
        parts = line.strip().split()
        task = {
            "name": parts[0],
            "deadline_period": int(parts[1]),
            "wcet": {
                "1188 Mhz": int(parts[2]),
                "918 Mhz": int(parts[3]),
                "648 Mhz": int(parts[4]),
                "384 Mhz": int(parts[5])
            },
            "deadline_misses": 0,
            "deadline": int(parts[1])
        }
        tasks.append(task)

    # Return the parsed data as a dictionary
    return {
        "num_tasks": num_tasks,
        "system_execution_time": system_execution_time,
        "cpu_powers": cpu_powers,
        "tasks": tasks
    }

def find_utilization(data, quota):
    #assuming base case where all taks run at max CPU power
    utilization = 0
    for task in data["tasks"]:
        utilization += task["wcet"]["1188 Mhz"] / task["deadline_period"]
    print(f"Utilization: {utilization}")
    if utilization > quota:
        return False
    return True

def calculate_energy(power, time):
    return power * time

def generate_edf_schedule(data):
    # Generate the Earliest Deadline First (EDF) schedule with preemption
    tasks = data["tasks"]
    tasks.sort(key=lambda x: x["deadline_period"])
    ready_queue = []
    time = 0
    running_task = None
    while time < data["system_execution_time"]:
        for task in tasks:
            if time % task["deadline_period"] == 0:
                ready_queue.append(copy.deepcopy(task)) #task added to ready queue
                print(f"Task {task['name']} added to ready queue at time {time}")
        ready_queue.sort(key=lambda x: x["deadline"]) #prioritize by deadline
        if len(ready_queue) > 0:
            if running_task is None or running_task["deadline"] > ready_queue[0]["deadline"]:
                if running_task is not None:
                    print(f"Task {running_task['name']} preempted at time {time}")
                running_task = ready_queue[0]
                print(f"Task {running_task['name']} running at time {time}")
            running_task["wcet"]["1188 Mhz"] -= 1
            if running_task["wcet"]["1188 Mhz"] == 0:
                print(f"Task {running_task['name']} completed at time {time}")
                original_task = next(task for task in tasks if task["name"] == running_task["name"])
                original_task["deadline"] += original_task["deadline_period"]
                ready_queue.pop(0)
                running_task = None
        else:
            print(f"Idle at time {time}")
        time += 1
            
    pass

def earliest_deadline_first(data, EE):
    quota = 1
    if not find_utilization(data, quota):
        print("Utilization exceeds quota")
        return
    print("Utilization is within quota")
    generate_edf_schedule(data)
    #sort tasks by deadline
    pass

def rate_monotonic(data, EE):
    # Implement the Rate Monotonic (RM) scheduling algorithm
    quota = data["num_tasks"] * ((2 ** (1/data["num_tasks"])) - 1)
    print(f"Quota: {quota}")
    if not find_utilization(data, quota):
        print("Utilization exceeds quota")
        return
    print("Utilization is within quota")
    pass

def main():
    if len(sys.argv) < 3:
        print("Usage: python solution.py <input_file> <scheduling_algorithm>")
        sys.exit(1)

    input_file = sys.argv[1]  # Grabbing the filename (e.g., input1.txt)
    scheduling_algorithm = sys.argv[2]  # Grabbing the scheduling algorithm (e.g., RM)
    EE = False
    print(f"Processing file: {input_file}")
    print(f"Scheduling Algorithm: {scheduling_algorithm}")

    # Parse the input file
    data = parse_file(input_file)

    # Implement the scheduling algorithm
    if scheduling_algorithm == "EE":
        print("Energy Efficient Scheduling")
        EE = True
        scheduling_algorithm = sys.argv[3]
    if scheduling_algorithm == "RM":
        rate_monotonic(data, EE)
    elif scheduling_algorithm == "EDF":
        earliest_deadline_first(data, EE)
    else:
        print("Invalid scheduling algorithm")
        sys.exit(1)

    # Output the parsed data (or you can proceed with the scheduling algorithm here)
    # print(data)

if __name__ == "__main__":
    main()
