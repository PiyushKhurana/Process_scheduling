A C++ program that simulates a basic CPU scheduler using Object-Oriented Programming (OOP) concepts like classes, polymorphism, and abstract classes. 
The program implements a **Process Scheduler** that can simulate different scheduling algorithms, such as **First-Come-First-Served (FCFS)**, **Round Robin (RR)**, and **Shortest Job Next (SJN)**.


### Explanation:

1. **Process Class (Abstract Base Class)**:
   - The `Process` class holds the common attributes for each process such as `processID`, `burstTime`, `arrivalTime`, `priority`, `waitingTime`, and `turnaroundTime`.
   - The `schedule` function is declared as pure virtual to be implemented in subclasses.

2. **Scheduling Algorithms**:
   - **FCFS (First-Come-First-Served)**: Implements scheduling based on the order of arrival. Processes are scheduled in the order they arrive, and each process waits until the previous one finishes.
   - **Round Robin (RR)**: Uses a time quantum to give each process a fair share of CPU time. If a process doesn’t finish within the quantum, it is placed back into the queue.
   - **Shortest Job Next (SJN)**: Sorts the processes based on their burst time and selects the shortest job available next.

3. **calculateAvgTimes Function**:
   - This function calculates and prints the average waiting and turnaround times based on the processes' data.

4. **Main Function**:
   - Creates a list of processes with attributes like burst time and arrival time.
   - Calls the scheduling algorithms (FCFS, Round Robin, and SJN) and displays the results.
   - Calculates the average waiting time and turnaround time for each algorithm.



### Key OOP Concepts:
- **Abstract Classes**: `Process` is an abstract class with a pure virtual method `schedule()`, making it a base for scheduling algorithms.
- **Polymorphism**: The `schedule()` method is overridden by the derived classes to implement different scheduling strategies without changing the core logic.
- **Inheritance**: `FCFS`, `RoundRobin`, and `ShortestJobNext` inherit from the `Process` class and implement their specific scheduling logic.

This program demonstrates the flexibility of using polymorphism to implement multiple scheduling algorithms while keeping the core process management logic consistent.

### Flow

```

+-------------------------+
|        Start             |
+-------------------------+
            |
            v
+-------------------------+
| Initialize Processes    |
| (Process ID, Burst Time,|
| Arrival Time, Priority) |
+-------------------------+
            |
            v
+-------------------------+
| Select Scheduling Algo  |----+
+-------------------------+    |
            |                 |
   +--------+---------+       |
   |                  |       |
   v                  v       v
+------------+   +------------+   +------------+
| FCFS       |   | Round Robin|   | SJN        |
| (Order by  |   | (Time Quantum, | (Shortest Job)|
| Arrival)   |   | Rotate Processes) | (Sort by burst)|
+------------+   +------------+   +------------+
            |                 |
            v                 v
+-------------------------+   +-------------------------+
| Calculate Waiting Time   |   | Calculate Waiting Time   |
| and Turnaround Time      |   | and Turnaround Time      |
+-------------------------+   +-------------------------+
            |                           |
            v                           v
+-------------------------+   +-------------------------+
| Calculate Avg Waiting    |   | Calculate Avg Waiting    |
| and Turnaround Times     |   | and Turnaround Times     |
+-------------------------+   +-------------------------+
            |                           |
            v                           v
+-------------------------+   +-------------------------+
| Output Results           |   | Output Results           |
+-------------------------+   +-------------------------+
            |                           |
            v                           v
+-------------------------+   +-------------------------+
|         End              |   |         End              |
+-------------------------+   +-------------------------+

```

1. **Start**  
    - Initialize process list with attributes: Process ID, Burst Time, Arrival Time, Priority (for SJN).

2. **Select Scheduling Algorithm**
    - **Decision Point**: Choose an algorithm (FCFS, Round Robin, or SJN).

3. **Apply Scheduling Algorithm**  
   - **FCFS**:
     - Processes are ordered by arrival time.
     - Execute each process sequentially.
     - Calculate waiting and turnaround times.
   
   - **Round Robin**:
     - Initialize a queue with processes.
     - Set time quantum.
     - Execute each process for a time slice (quantum).
     - If a process doesn’t finish, place it back into the queue.
     - Calculate waiting and turnaround times for each process.
   
   - **Shortest Job Next (SJN)**:
     - Sort processes by burst time.
     - Execute the shortest process first.
     - Calculate waiting and turnaround times.

4. **Calculate Waiting Time and Turnaround Time**
   - For each process, compute the waiting time (time spent in the ready queue) and the turnaround time (total time from arrival to completion).

5. **Calculate Average Waiting and Turnaround Times**
   - Calculate the average waiting time and average turnaround time across all processes for the selected algorithm.

6. **Output Results**
   - Display the calculated average waiting time and turnaround time.

7. **End**


### Output:

```
FCFS Scheduling:
Average Waiting Time: 5.25
Average Turnaround Time: 9.25

Round Robin Scheduling:
Average Waiting Time: 5.00
Average Turnaround Time: 9.00

Shortest Job Next Scheduling:
Average Waiting Time: 4.25
Average Turnaround Time: 8.25
```