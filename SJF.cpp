#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Process {
public:
    int pID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    bool isCompleted;

    Process(int pID, int arrivalTime, int burstTime) {
        this->pID = pID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->completionTime = 0;
        this->turnAroundTime = 0;
        this->waitingTime = 0;
        this->isCompleted = false;
    }

    void display() const {
        cout << "Process ID: " << pID << ", Arrival Time: " << arrivalTime
             << ", Burst Time: " << burstTime << ", Completion Time: " << completionTime 
             << ", Waiting Time: " << waitingTime
             << ", Turnaround Time: " << turnAroundTime << endl;
    }
};

int main() {
    int n;
    cout << "Enter the Number of Processes for SJF (Non-Preemptive): ";
    cin >> n;

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

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int minBurstTime = INT_MAX;
        int selectedProcess = -1;

        // Find the process with the shortest burst time among the arrived ones
        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurstTime) {
                    minBurstTime = processes[i].burstTime;
                    selectedProcess = i;
                }
                // Break ties by selecting the process with the earlier arrival time
                else if (processes[i].burstTime == minBurstTime) {
                    if (processes[i].arrivalTime < processes[selectedProcess].arrivalTime) {
                        selectedProcess = i;
                    }
                }
            }
        }

        if (selectedProcess == -1) {
            // No process has arrived, so advance time to the arrival time of the next process
            currentTime++;
        } else {
            // Process the selected process
            processes[selectedProcess].waitingTime = currentTime - processes[selectedProcess].arrivalTime;
            processes[selectedProcess].completionTime = currentTime + processes[selectedProcess].burstTime;
            processes[selectedProcess].turnAroundTime = processes[selectedProcess].completionTime - processes[selectedProcess].arrivalTime;

            currentTime += processes[selectedProcess].burstTime;
            processes[selectedProcess].isCompleted = true;
            completed++;
        }
    }

    cout << "\nProcess Scheduling Results (SJF Non-Preemptive):\n";
    for (size_t i = 0; i < processes.size(); i++) {
    processes[i].display();
    }

    double avgWaitingTime = 0;
    double avgTurnAroundTime = 0;
    for (size_t i = 0; i < processes.size(); i++) {
    avgWaitingTime += processes[i].waitingTime;
    avgTurnAroundTime += processes[i].turnAroundTime;
    }
    avgWaitingTime /= n;
    avgTurnAroundTime /= n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}
