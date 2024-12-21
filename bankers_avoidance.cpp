# include <iostream>
# include <vector>
using namespace std;

void initialize(int &n, int &m, vector<int> &available,
vector<vector<int> > &allocation, vector<vector<int> > &max, vector<vector<int> > &need){
     cout<<"Enter number of processes"; cin>>n;
     cout<<"Enter number of resource types"; cin>>m;
     allocation.assign(n, vector<int>(m, 0));
     max.assign(n, vector<int>(m, 0));
     need.assign(n, vector<int>(m, 0));
     available.assign(m, 0);
     cout<<"Enter number of available resources of each type:"<<endl;
     for(int i = 0; i < m; i++) cin>>available[i];
     for(int i = 0; i < n; i++){
        cout<<"Enter maximum demand of each resource type for process "<<i+1<<":"<<endl;
        for(int j = 0; j < m; j++) cin>>max[i][j];
     }
     for(int i = 0; i < n; i++){
        cout<<"Enter number of allocated resources of each resource type for process "<<i+1<<":"<<endl;
        for(int j = 0; j < m; j++) cin>>allocation[i][j];
     }
     for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
     }
}

bool is_less_equal(vector<int> &x, vector<int> &y){
    int n = x.size();
    for(int i = 0; i < n; i++){
        if(x[i] > y[i]) return false;
    }
    return true;
}

void add(vector<int> &x, vector<int> &y){
    int n = y.size();
    for(int i = 0; i < n; i++){
        x[i] += y[i];
    }
}

bool bankers_algorithm(int &n, int &m, vector<int> &available,
vector<vector<int> > &allocation, vector<vector<int> > &max, vector<vector<int> > &need){
    vector<int> work(available.begin(), available.end());
    vector<int> finish(n, false);
    vector<int> safe_sequence;
    bool found = false;
    do{
        found = false;
        for(int i = 0; i < n; i++){
            if(finish[i]==false){
                if(is_less_equal(need[i], work)){
                    add(work, allocation[i]);
                    safe_sequence.push_back(i+1);
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while(found);
    bool all_finished = true;
    for(int i = 0; i < n; i++){
        if(finish[i]==false) all_finished = false;
    }
    if(all_finished){
        cout<<"Possible Safe Sequence for given set of process and resources:"<<endl;
        for(int i = 0; i < n; i++) cout<<safe_sequence[i]<<" ";
        cout<<endl;
        return true;
    }
    else return false;
}

int main(){
    int n, m;
    vector<int> available;
    vector<vector<int> > allocation, max, need;
    initialize(n, m, available, allocation, max, need);
    bool is_safe = bankers_algorithm(n, m, available, allocation, max, need);
    if(is_safe) cout<<"The system is in safe state, and deadlock has been avoided"<<endl;
    else cout<<"The system is in unsafe state, and deadlock can not be avoided"<<endl;
}