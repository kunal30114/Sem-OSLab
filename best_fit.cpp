#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

class process{
    public:
        int process_id;
        int memory_required;
};

class block{
    public:
        int block_id;
        int memory;
        bool free;
};

void input_processes(int n, process arr[]){
    for(int i = 0; i < n; i++){
        cout<<"Enter memory_required in process "<<i+1<<": "; cin>>arr[i].memory_required;
        arr[i].process_id = i + 1;
    }
};

void input_memory_blocks(int m, block arr[]){
    for(int i = 0; i < m; i++){
        cout<<"Enter memory in block "<<i+1<<": "; cin>>arr[i].memory;
        arr[i].block_id = i + 1;
        arr[i].free = true;
    }
};

bool compare(block &b1, block &b2){
    if(b1.memory==b2.memory) return b1.block_id < b2.block_id;
    return b1.memory > b2.memory;
}

const int inf = (1<<30);

int main(){
    int n; cout<<"Enter number of processes: "; cin>>n;
    process arr[n];
    input_processes(n, arr);
    int m; cout<<"Enter number of memory blocks: "; cin>>m;
    block arr2[m]; 
    input_memory_blocks(m, arr2);
    cout<<"Process_ID\tBlock_ID\tMemory_Used\tMemory_wasted\n";
    for(int j = 0; j < n; j++){
        int best_memory = inf, k = -1;
        for(int i = 0; i < m; i++){
            if(arr2[i].free && arr2[i].memory >= arr[j].memory_required){
                if(best_memory > arr2[i].memory){
                    best_memory = arr2[i].memory;
                    k = i;
                }
            }
        }
        if(k==-1){
            cout<<arr[j].process_id<<"\t\tNA\t\tNA\t\tNA\n";
        }
        else{
            cout<<arr[j].process_id<<"\t\t"<<arr2[k].block_id<<"\t\t"<<
            arr[j].memory_required<<"\t\t"<<arr2[k].memory - arr[j].memory_required<<endl;
            arr2[k].free = false;
        }
    }
}