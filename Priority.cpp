#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Process {
public:
    int pID;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int remainingBurstTime;

    Process(int pID, int arrivalTime, int burstTime, int priority) 
        : pID(pID), arrivalTime(arrivalTime), burstTime(burstTime), priority(priority) {
        completionTime = waitingTime = turnAroundTime = 0;
        remainingBurstTime = burstTime;
    }

    void display() const {
        cout << "Process ID: " << pID << ", Arrival Time: " << arrivalTime
             << ", Burst Time: " << burstTime << ", Priority: " << priority
             << ", Completion Time: " << completionTime << ", Waiting Time: " << waitingTime
             << ", Turnaround Time: " << turnAroundTime << endl;
    }
};

// Comparator for priority queue (higher priority, lower arrival time first)
struct compare {
    bool operator()(const Process* a, const Process* b) {
        if (a->priority == b->priority) 
            return a->arrivalTime > b->arrivalTime;
        return a->priority > b->priority;
    }
};

int main() {
    int n;
    cout << "Enter the Number of Processes for Preemptive Priority Scheduling: ";
    cin >> n;

    vector<Process> processes;

    for (int i = 0; i < n; i++) {
        int pID, arrivalTime, burstTime, priority;
        cout << "Enter pID: ";
        cin >> pID;
        cout << "Enter Arrival Time: ";
        cin >> arrivalTime;
        cout << "Enter Burst Time: ";
        cin >> burstTime;
        cout << "Enter Priority (Lower value means higher priority): ";
        cin >> priority;

        processes.push_back(Process(pID, arrivalTime, burstTime, priority));
    }

    priority_queue<Process*, vector<Process*>, compare> pq;
    int currentTime = 0, totalWaitingTime = 0, totalTurnaroundTime = 0;
    int completed = 0;
    
    // Main loop: increment time until all processes are complete
    while (completed < n) {
        // Add all arriving processes at current time to the queue
        for (auto &proc : processes) {
            if (proc.arrivalTime == currentTime) {
                pq.push(&proc);
            }
        }

        // If queue is not empty, process the highest priority process
        if (!pq.empty()) {
            Process* currentProcess = pq.top();
            pq.pop();        
            // Execute process for 1 unit time
            currentProcess->remainingBurstTime--;
            currentTime++;
            // If process is completed
            if (currentProcess->remainingBurstTime == 0) {
                completed++;
                currentProcess->completionTime = currentTime;
                currentProcess->turnAroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnAroundTime - currentProcess->burstTime;
                
                totalWaitingTime += currentProcess->waitingTime;
                totalTurnaroundTime += currentProcess->turnAroundTime;
            } else {
                // If not completed, re-add to queue
                pq.push(currentProcess);
            }
        } else {
            currentTime++;  // Increment time if no process is available
        }
    }

    cout << "\nProcess Scheduling Results (Priority Preemptive):\n";
    for (size_t i = 0; i < processes.size(); i++) {
    processes[i].display();
    }
    
    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnAroundTime = (double)totalTurnaroundTime / n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}
