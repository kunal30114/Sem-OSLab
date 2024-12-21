#include <iostream>
#include <vector>
#include <queue>  
#include <set>  
#include <algorithm>  
using namespace std;


struct Compare {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        return a[0] < b[0];  // sort by the second element in non-decreasing order
    }
};

int main(){
    set<vector<int>> list;
    int n;
    cout<<"Enter Number of process : ";
    cin>>n;
    //[arraival time , burst time , remaining time , p_id]
    set<vector<int> , Compare> s;

    for (int i = 0; i < n; i++)
    {
        int at,bt,rt,pid;
        cin>>at>>bt>>rt>>pid;
        vector<int> temp;
        
        temp.push_back(at);
        temp.push_back(bt);
        temp.push_back(rt);
        temp.push_back(pid);
        s.insert(temp);

        
        
    }
    vector<int> ct(n);
    vector<int> tat(n);
    int time_quant = 2;
    int curr_time = 0;
    while(s.empty()!=1){
    for(auto i : s){
       




    }}



    
}