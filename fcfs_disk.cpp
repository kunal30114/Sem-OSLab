#include <iostream>
#include <vector>
#include <cmath>  // For abs function
using namespace std;

class DiskScheduler {
    vector<int> request_sequence;
    vector<int> seek_sequence;
    int head;
    int seek_time;
    const int disk_size;

public:
    DiskScheduler(int disk_size = 200) : disk_size(disk_size), seek_time(0), head(0) {}

    void initialize() {
        int n;
        cout << "Enter the number of tracks in request sequence: ";
        cin >> n;
        
        request_sequence.resize(n);
        cout << "Enter request sequence: ";
        for (int &track : request_sequence) cin >> track;

        cout << "Enter initial head position: ";
        cin >> head;
    }

    void fcfs() {
        seek_time = 0;
        seek_sequence.clear();
        
        for (int track : request_sequence) {
            cout << "Head moving from " << head << " to " << track << endl;
            seek_sequence.push_back(track);

            int distance = abs(track - head);
            seek_time += distance;
            head = track;
        }

        display_result();
    }

private:
    void display_result() const {
        cout << "Total Seek Time: " << seek_time << endl;
        cout << "Seek Sequence: ";
        for (int track : seek_sequence) cout << track << " ";
        cout << endl;
    }
};

int main() {
    DiskScheduler scheduler;
    scheduler.initialize();
    scheduler.fcfs();
}
