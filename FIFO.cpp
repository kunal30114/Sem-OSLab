# include <iostream>
# include <vector>
# include <queue>
# include <set>
using namespace std;

int num_frames, num_pages;
queue<int> frames;
set<int> pages_in_memory;
vector<int> page_reference_string;

void initialize(){
    cout<<"Enter maximum number of frames: "<<endl; cin>>num_frames;
    cout<<"Enter number of pages to be entered: "<<endl; cin>>num_pages;
    page_reference_string.assign(num_pages, 0);
    cout<<"Enter page sequence: ";
    for(int i = 0; i < num_pages; i++) cin>>page_reference_string[i];
}

void fifo(){
    int page_faults = 0;
    for(int i = 0; i < num_pages; i++){
        if(pages_in_memory.find(page_reference_string[i]) != pages_in_memory.end()){
            cout<<"Page "<<page_reference_string[i]<<" in memory"<<endl;
        }
        else{
            cout<<"Page fault occurred"<<endl;
            if(frames.size() == num_frames){
                int replaced_page = frames.front(); frames.pop();
                pages_in_memory.erase(replaced_page);
                cout<<"Page "<<replaced_page<<" has been swapped out"<<endl;
            }
            pages_in_memory.insert(page_reference_string[i]);
            frames.push(page_reference_string[i]);
            cout<<"Page "<<page_reference_string[i]<<" has been swapped in"<<endl;
            page_faults++;
        }
    }
    cout<<"Number of hits = "<<num_pages - page_faults<<endl;
    cout<<"Number of misses = "<<page_faults<<endl;
}

int main(){
    initialize();
    fifo();
}