#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Process {
public:
    int processID;
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    int turnaroundTime;

    Process(int pid, int bt, int at, int pr = 0)
        : processID(pid), burstTime(bt), arrivalTime(at), priority(pr), waitingTime(0), turnaroundTime(0) {}
};

class Scheduler {
public:
    virtual void schedule(vector<Process*>& processes) = 0;
    

    static void calculateAvgTimes(const vector<Process*>& processes) {
        double totalWaitingTime = 0, totalTurnaroundTime = 0;
        for (const auto& p : processes) {
            totalWaitingTime += p->waitingTime;
            totalTurnaroundTime += p->turnaroundTime;
        }
        cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << "\n";
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processes.size() << "\n";
    }
};

class FCFS : public Scheduler {
public:
    void schedule(vector<Process*>& processes)  {
        sort(processes.begin(), processes.end(), compareArrivalTime);
        int currentTime = 0;
        for (auto& p : processes) {
            currentTime = max(currentTime, p->arrivalTime);
            p->waitingTime = currentTime - p->arrivalTime;
            p->turnaroundTime = p->waitingTime + p->burstTime;
            currentTime += p->burstTime;
        }
    }

    static bool compareArrivalTime(Process* a, Process* b) {
        return a->arrivalTime < b->arrivalTime;
    }
};

class RoundRobin : public Scheduler {
public:
    int quantumTime;
     RoundRobin(int qt) : quantumTime(qt) {}

    void schedule(vector<Process*>& processes)  {
        queue<Process*> processQueue;
        vector<int> remainingTime(processes.size());
        int currentTime = 0, index = 0;

        // Sort processes by arrival time
        sort(processes.begin(), processes.end(), compareArrivalTime);

        while (index < processes.size() || !processQueue.empty()) {
            // Add processes to queue if they have arrived
            while (index < processes.size() && processes[index]->arrivalTime <= currentTime) {
                processQueue.push(processes[index]);
                index++;
            }

            if (!processQueue.empty()) {
                Process* currentProcess = processQueue.front();
                processQueue.pop();
                int processIndex = currentProcess->processID - 1;

                if (remainingTime[processIndex] > quantumTime) {
                    currentTime += quantumTime;
                    remainingTime[processIndex] -= quantumTime;
                    processQueue.push(currentProcess);
                } else {
                    currentTime += remainingTime[processIndex];
                    currentProcess->waitingTime = currentTime - currentProcess->arrivalTime - currentProcess->burstTime;
                    currentProcess->turnaroundTime = currentTime - currentProcess->arrivalTime;
                    remainingTime[processIndex] = 0;
                }
            } else {
                // Jump to the next process arrival if no process is available
                currentTime = processes[index]->arrivalTime;
            }
        }
    }

    static bool compareArrivalTime(Process* a, Process* b) {
        return a->arrivalTime < b->arrivalTime;
    }
};


class ShortestJobNext : public Scheduler {
public:
    void schedule(vector<Process*>& processes)  {
        priority_queue<Process*, vector<Process*>, CompareBurstTime> pq;
        
        sort(processes.begin(), processes.end(), compareArrivalTime);
        
        int currentTime = 0, index = 0;
        while (index < processes.size() || !pq.empty()) {
            while (index < processes.size() && processes[index]->arrivalTime <= currentTime) {
                pq.push(processes[index]);
                index++;
            }
            if (!pq.empty()) {
                Process* p = pq.top(); pq.pop();
                p->waitingTime = currentTime - p->arrivalTime;
                p->turnaroundTime = p->waitingTime + p->burstTime;
                currentTime += p->burstTime;
            } else {
                currentTime = processes[index]->arrivalTime;
            }
        }
    }

    struct CompareBurstTime {
        bool operator()(Process* a, Process* b) {
            return a->burstTime > b->burstTime;
        }
    };

    static bool compareArrivalTime(Process* a, Process* b) {
        return a->arrivalTime < b->arrivalTime;
    }
};

int main() {
    vector<Process*> processes = {
        new Process(1, 6, 0),
        new Process(2, 8, 1),
        new Process(3, 7, 2),
        new Process(4, 3, 3)
    };

    FCFS fcfsScheduler;
    fcfsScheduler.schedule(processes);
    cout << "FCFS Scheduling:\n";
    Scheduler::calculateAvgTimes(processes);

    for (auto& p : processes) p->waitingTime = p->turnaroundTime = 0;
    RoundRobin rrScheduler(4);
    rrScheduler.schedule(processes);
    cout << "\nRound Robin Scheduling:\n";
    Scheduler::calculateAvgTimes(processes);

    for (auto& p : processes) p->waitingTime = p->turnaroundTime = 0;
    ShortestJobNext sjnScheduler;
    sjnScheduler.schedule(processes);
    cout << "\nShortest Job Next Scheduling:\n";
    Scheduler::calculateAvgTimes(processes);

    for (auto p : processes) delete p;
    return 0;
}
