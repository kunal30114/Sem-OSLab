#include <iostream>
#include <vector>
using namespace std;

void setup_resources(int &num_processes, int &num_resources, int &requesting_process, vector<int> &available_resources,
                     vector<vector<int> > &allocated_resources, vector<vector<int> > &max_demand,
                     vector<vector<int> > &remaining_need, vector<int> &requested_resources) {
    cout << "Enter number of processes: ";
    cin >> num_processes;
    cout << "Enter number of resource types: ";
    cin >> num_resources;

    allocated_resources.assign(num_processes, vector<int>(num_resources, 0));
    max_demand.assign(num_processes, vector<int>(num_resources, 0));
    remaining_need.assign(num_processes, vector<int>(num_resources, 0));
    available_resources.assign(num_resources, 0);
    requested_resources.assign(num_resources, 0);

    cout << "Enter available resources for each type:\n";
    for (int i = 0; i < num_resources; i++) cin >> available_resources[i];

    for (int i = 0; i < num_processes; i++) {
        cout << "Enter maximum demand for each resource for process " << i + 1 << ":\n";
        for (int j = 0; j < num_resources; j++) cin >> max_demand[i][j];
    }

    for (int i = 0; i < num_processes; i++) {
        cout << "Enter allocated resources for each type for process " << i + 1 << ":\n";
        for (int j = 0; j < num_resources; j++) cin >> allocated_resources[i][j];
    }

    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            remaining_need[i][j] = max_demand[i][j] - allocated_resources[i][j];
        }
    }

    cout << "Enter process ID making the request: ";
    cin >> requesting_process;
    requesting_process--;

    cout << "Enter requested instances of each resource for process " << requesting_process + 1 << ":\n";
    for (int j = 0; j < num_resources; j++) cin >> requested_resources[j];
}

bool can_fulfill_request(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] > b[i]) return false;
    }
    return true;
}

void increase(vector<int> &target, vector<int> &source) {
    for (int i = 0; i < source.size(); i++) {
        target[i] += source[i];
    }
}

void decrease(vector<int> &target, vector<int> &source) {
    for (int i = 0; i < source.size(); i++) {
        target[i] -= source[i];
    }
}

bool check_safety(int &num_processes, int &num_resources, vector<int> &available_resources,
                  vector<vector<int> > &allocated_resources, vector<vector<int> > &remaining_need) {
    vector<int> work = available_resources;
    vector<bool> finished(num_processes, false);
    bool process_allocated = false;

    do {
        process_allocated = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finished[i] && can_fulfill_request(remaining_need[i], work)) {
                increase(work, allocated_resources[i]);
                finished[i] = true;
                process_allocated = true;
            }
        }
    } while (process_allocated);

    for (bool status : finished) {
        if (!status) return false;
    }
    return true;
}

void handle_request(int &num_processes, int &num_resources, int &requesting_process, vector<int> &available_resources,
                    vector<vector<int> > &allocated_resources, vector<vector<int> > &remaining_need, vector<int> &requested_resources) {
    if (!can_fulfill_request(requested_resources, remaining_need[requesting_process])) {
        cout << "Request exceeds maximum claim for process " << requesting_process + 1 << ".\n";
        return;
    }

    if (!can_fulfill_request(requested_resources, available_resources)) {
        cout << "Resources unavailable for process " << requesting_process + 1 << ". Process must wait.\n";
        return;
    }

    decrease(available_resources, requested_resources);
    increase(allocated_resources[requesting_process], requested_resources);
    decrease(remaining_need[requesting_process], requested_resources);

    if (check_safety(num_processes, num_resources, available_resources, allocated_resources, remaining_need)) {
        cout << "Resources allocated to process " << requesting_process + 1 << " successfully. No deadlock detected.\n";
    } else {
        cout << "Allocation denied to avoid deadlock.\n";
        increase(available_resources, requested_resources);
        decrease(allocated_resources[requesting_process], requested_resources);
        increase(remaining_need[requesting_process], requested_resources);
    }
}

int main() {
    int num_processes, num_resources, requesting_process;
    vector<int> available_resources;
    vector<int> requested_resources;
    vector<vector<int> > allocated_resources, max_demand, remaining_need;

    setup_resources(num_processes, num_resources, requesting_process, available_resources, allocated_resources, max_demand, remaining_need, requested_resources);
    handle_request(num_processes, num_resources, requesting_process, available_resources, allocated_resources, remaining_need, requested_resources);

    return 0;
}