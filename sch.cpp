#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

// Abstract base class for Process
class Process {
public:
    int processID;   // Process ID
    int burstTime;   // Burst time (CPU time required)
    int arrivalTime; // Arrival time
    int priority;    // Priority for scheduling algorithms (if applicable)
    int waitingTime; // Waiting time
    int turnaroundTime; // Turnaround time

    Process(int pid, int bt, int at, int pr = 0) : processID(pid), burstTime(bt), arrivalTime(at), priority(pr), waitingTime(0), turnaroundTime(0) {}
    
    virtual ~Process() = default;
    
    virtual void schedule(std::vector<Process*>& readyQueue) = 0; // Abstract method to schedule the process
};

// FCFS Scheduling (First-Come-First-Served) Algorithm
class FCFS : public Process {
public:
    FCFS(int pid, int bt, int at) : Process(pid, bt, at) {}
    
    void schedule(std::vector<Process*>& readyQueue) override {
        int currentTime = 0;
        
        for (auto& p : readyQueue) {
            if (currentTime < p->arrivalTime) {
                currentTime = p->arrivalTime;
            }
            p->waitingTime = currentTime - p->arrivalTime;
            p->turnaroundTime = p->waitingTime + p->burstTime;
            currentTime += p->burstTime;
        }
    }
};

// Round Robin Scheduling Algorithm
class RoundRobin : public Process {
public:
    int quantumTime; // Time quantum for Round Robin
    
    RoundRobin(int pid, int bt, int at, int qt) : Process(pid, bt, at), quantumTime(qt) {}
    
    void schedule(std::vector<Process*>& readyQueue) override {
        int currentTime = 0;
        std::queue<Process*> processQueue;
        
        // Initialize the queue with processes
        for (auto& p : readyQueue) {
            processQueue.push(p);
        }
        
        while (!processQueue.empty()) {
            Process* currentProcess = processQueue.front();
            processQueue.pop();
            
            if (currentProcess->burstTime > quantumTime) {
                currentProcess->burstTime -= quantumTime;
                currentTime += quantumTime;
                processQueue.push(currentProcess);
            } else {
                currentTime += currentProcess->burstTime;
                currentProcess->waitingTime = currentTime - currentProcess->arrivalTime - currentProcess->burstTime;
                currentProcess->turnaroundTime = currentTime - currentProcess->arrivalTime;
                currentProcess->burstTime = 0;
            }
        }
    }
};

// Shortest Job Next Scheduling Algorithm
class ShortestJobNext : public Process {
public:
    ShortestJobNext(int pid, int bt, int at) : Process(pid, bt, at) {}
    
    void schedule(std::vector<Process*>& readyQueue) override {
        int currentTime = 0;
        
        // Sort the readyQueue based on burstTime (Shortest Job First)
        std::sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
            return a->burstTime < b->burstTime;
        });
        
        for (auto& p : readyQueue) {
            if (currentTime < p->arrivalTime) {
                currentTime = p->arrivalTime;
            }
            p->waitingTime = currentTime - p->arrivalTime;
            p->turnaroundTime = p->waitingTime + p->burstTime;
            currentTime += p->burstTime;
        }
    }
};

// Function to calculate and display average waiting and turnaround times
void calculateAvgTimes(const std::vector<Process*>& processes) {
    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (const auto& p : processes) {
        totalWaitingTime += p->waitingTime;
        totalTurnaroundTime += p->turnaroundTime;
    }
    
    std::cout << "Average Waiting Time: " << std::fixed << std::setprecision(2) << totalWaitingTime / processes.size() << std::endl;
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << totalTurnaroundTime / processes.size() << std::endl;
}

int main() {
    std::vector<Process*> processes;
    
    // Creating a few processes (Process ID, Burst Time, Arrival Time, [Priority])
    processes.push_back(new FCFS(1, 6, 0));
    processes.push_back(new FCFS(2, 8, 1));
    processes.push_back(new FCFS(3, 7, 2));
    processes.push_back(new FCFS(4, 3, 3));
    
    // Scheduling algorithms
    FCFS fcfs(0, 0, 0);  // We use FCFS as a scheduling algorithm
    fcfs.schedule(processes);
    std::cout << "FCFS Scheduling:\n";
    calculateAvgTimes(processes);

    // Resetting burst time for the processes for other algorithms
    processes[0]->burstTime = 6;
    processes[1]->burstTime = 8;
    processes[2]->burstTime = 7;
    processes[3]->burstTime = 3;
    
    // Round Robin Scheduling (time quantum = 4)
    RoundRobin rr(0, 0, 0, 4);
    rr.schedule(processes);
    std::cout << "\nRound Robin Scheduling:\n";
    calculateAvgTimes(processes);

    // Resetting burst time for the processes for other algorithms
    processes[0]->burstTime = 6;
    processes[1]->burstTime = 8;
    processes[2]->burstTime = 7;
    processes[3]->burstTime = 3;

    // Shortest Job Next Scheduling
    ShortestJobNext sjn(0, 0, 0);
    sjn.schedule(processes);
    std::cout << "\nShortest Job Next Scheduling:\n";
    calculateAvgTimes(processes);

    // Cleaning up dynamically allocated memory
    for (auto p : processes) {
        delete p;
    }

    return 0;
}
