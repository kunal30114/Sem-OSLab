#include <iostream>
#include <vector>
#include <algorithm> 
#include <cmath>     
using namespace std;

class DiskScheduler {
    vector<int> request_sequence;
    vector<int> seek_sequence;
    string direction;
    int head;
    int seek_time;
    const int disk_size;

public:
    DiskScheduler(int disk_size = 200) 
        : disk_size(disk_size), head(0), seek_time(0), direction("left") {}

    void initialize() {
        int n;
        cout << "Enter number of tracks in request sequence: ";
        cin >> n;

        request_sequence.resize(n);
        cout << "Enter request sequence: ";
        for (int &track : request_sequence) cin >> track;

        cout << "Enter initial head position: ";
        cin >> head;

        cout << "Enter initial direction of movement (left/right): ";
        cin >> direction;
    }

    void scan() {
        vector<int> left, right;
        if (direction == "left") left.push_back(0);
        else if (direction == "right") right.push_back(disk_size - 1);

        for (int track : request_sequence) {
            if (track < head) left.push_back(track);
            if (track > head) right.push_back(track);
        }

        sort(left.begin(), left.end());
        sort(right.begin(), right.end());

        process_tracks(left, right);
        display_result();
    }

private:
    void process_tracks(vector<int> &left, vector<int> &right) {
        int runs = 2;
        while (runs--) {
            if (direction == "left") {

                for (auto it = left.rbegin(); it != left.rend(); ++it) {
                    move_head_to(*it);
                }
                direction = "right"; 
            } else if (direction == "right") {

                for (int track : right) {
                    move_head_to(track);
                }
                direction = "left"; 
            }
        }
    }

    void move_head_to(int track) {
        cout << "Head has moved from " << head << " to " << track << endl;
        seek_sequence.push_back(track);

        int distance = abs(track - head);
        seek_time += distance;
        head = track;
    }

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
    scheduler.scan();
}
