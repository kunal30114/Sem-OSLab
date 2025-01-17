//Round Robin Implementation
#include <iostream>
#include <vector>
#include <queue> 
using namespace std;

class Process {
public:
    int pID;
    int arrivalTime;
    int burstTime;
    int remainingTime; 
    int completionTime;
    int waitingTime;
    int turnAroundTime;

    Process(int pID, int arrivalTime, int burstTime) {
        this->pID = pID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->remainingTime = burstTime;  
        this->completionTime = 0;
        this->waitingTime = 0;
        this->turnAroundTime = 0;
    }
    
    void display() const {
        cout << "Process ID: " << pID << ", Arrival Time: " << arrivalTime
             << ", Burst Time: " << burstTime << ", Completion Time: " << completionTime
             << ", Waiting Time: " << waitingTime << ", Turnaround Time: " << turnAroundTime << endl;
    }
};

int main() {
    int n, timeQuantum;
    cout << "Enter the Number of Processes for Round Robin: ";
    cin >> n;
    
    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    vector<Process> processes;

    
    for (int i = 0; i < n; i++) {
        int pID, arrivalTime, burstTime;
        cout << "Enter pID: ";
        cin >> pID;
        cout << "Enter Arrival Time: ";
        cin >> arrivalTime;
        cout << "Enter Burst Time: ";
        cin >> burstTime;

        processes.push_back(Process(pID, arrivalTime, burstTime));
    }

    queue<int> readyQueue;  
    int currentTime = 0;
    int completed = 0;
    vector<bool> isInQueue(n, false);  
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && !isInQueue[i]) {
            readyQueue.push(i);
            isInQueue[i] = true;
        }
    }

    while (completed < n) {
        if (!readyQueue.empty()) {
            int idx = readyQueue.front();
            readyQueue.pop();
            // Process this process for either the time quantum or its remaining time
            int timeToExecute = min(timeQuantum, processes[idx].remainingTime);
            processes[idx].remainingTime -= timeToExecute;
            currentTime += timeToExecute;
            // Check if the process is completed
            if (processes[idx].remainingTime == 0) {
                completed++;
                processes[idx].completionTime = currentTime;
                processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
                totalWaitingTime += processes[idx].waitingTime;
                totalTurnaroundTime += processes[idx].turnAroundTime;
            }
            // Add new processes that have arrived during the current time to the ready queue
            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime <= currentTime && !isInQueue[i] && processes[i].remainingTime > 0) {
                    readyQueue.push(i);
                    isInQueue[i] = true;
                }
            }
            // If the process is not finished, push it back to the ready queue
            if (processes[idx].remainingTime > 0) {
                readyQueue.push(idx);
            }

        } else {
            // If the ready queue is empty, increment the current time until a process arrives
            currentTime++;
        }
    }

    cout << "\nProcess Scheduling Results (Round Robin):\n";
    for (const auto &p : processes) {
        p.display();
    }

    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnAroundTime = (double)totalTurnaroundTime / n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}
