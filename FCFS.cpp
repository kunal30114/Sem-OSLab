// First Come First Serve Implementation


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
public:
    int pID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;

    Process(int pID, int arrivalTime, int burstTime) {
        this->pID = pID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->completionTime=0;
        this->turnAroundTime = 0;
        this->waitingTime = 0;
    }

    void display() const {
        cout << "Process ID: " << pID << ", Arrival Time: " << arrivalTime
             << ", Burst Time: " << burstTime << ", Completion Time: " << completionTime << ", Waiting Time: " << waitingTime
             << ", Turnaround Time: " << turnAroundTime << endl;
    }
};

bool compareArrivalTime(const Process &p1, const Process &p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the Number of Processes for FCFS: ";
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

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;

    for (int i = 0; i < n; i++) {

        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime; 
        }

        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        processes[i].completionTime = currentTime + processes[i].burstTime;

        currentTime += processes[i].burstTime;
       
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

      
        
    }

   
    cout << "\nProcess Scheduling Results (FCFS):\n";
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
