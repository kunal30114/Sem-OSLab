# include <iostream>
# include <map>
# include <set>
using namespace std;

int num_frames, num_pages;
set<int> frames;
map<int, int> frequency;
vector<int> page_reference_string;

void initialize(){
    cout<<"Enter maximum number of frames: "<<endl; cin>>num_frames;
    cout<<"Enter number of pages to be entered: "<<endl; cin>>num_pages;
    page_reference_string.assign(num_pages, 0);
    cout<<"Enter page sequence: ";
    for(int i = 0; i < num_pages; i++) cin>>page_reference_string[i];
}

void lfu(){
    int page_faults = 0;
    for(int i = 0; i < num_pages; i++){
        if(frames.find(page_reference_string[i]) != frames.end()){
            cout<<"Page "<<page_reference_string[i]<<" in memory"<<endl;
            frequency[page_reference_string[i]]++;
        }
        else{
            cout<<"Page fault occurred"<<endl;
            if(frames.size() == num_frames){
                int replaced_page = *frames.begin(); 
                int least_frequency = frequency[replaced_page];
                for(int f: frames){
                    if(frequency[f] < least_frequency){
                        replaced_page = f;
                        least_frequency = frequency[f];
                    }
                }
                frames.erase(replaced_page);
                cout<<"Page "<<replaced_page<<" has been swapped out"<<endl;
            }
            frequency[page_reference_string[i]] = 1;
            frames.insert(page_reference_string[i]);
            cout<<"Page "<<page_reference_string[i]<<" has been swapped in"<<endl;
            page_faults++;
        }
    }
    cout<<"Number of hits = "<<num_pages - page_faults<<endl;
    cout<<"Number of misses = "<<page_faults<<endl;
}

int main(){
    initialize();
    lfu();
}