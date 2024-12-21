# include <iostream>
# include <set>
# include <map>
using namespace std;

int num_frames, num_pages;
set<int> frames;
vector<int> page_reference_string;

void initialize(){
    cout<<"Enter maximum number of frames: "<<endl; cin>>num_frames;
    cout<<"Enter number of pages to be entered: "<<endl; cin>>num_pages;
    page_reference_string.assign(num_pages, 0);
    cout<<"Enter page sequence: ";
    for(int i = 0; i < num_pages; i++) cin>>page_reference_string[i];
}

int predict(int i){
    map<int, int> farthest;
    for(int j = num_pages - 1; j > i; j--){
        farthest[page_reference_string[j]] = j + 1;
    }
    int farthest_page = *frames.begin(); 
    int farthest_occurence = farthest[farthest_page];
    for(int f: frames){
        if(farthest[f] < farthest_occurence){
            farthest_page = f;
            farthest_occurence = farthest[f];
        }
    }
    return farthest_page;
}

void optimal(){
    int page_faults = 0;
    for(int i = 0; i < num_pages; i++){
        if(frames.find(page_reference_string[i]) != frames.end()){
            cout<<"Page "<<page_reference_string[i]<<" in memory"<<endl;
        }
        else{
            cout<<"Page fault occurred"<<endl;
            if(frames.size() == num_frames){
                int replaced_page = predict(i);
                frames.erase(replaced_page);
                cout<<"Page "<<replaced_page<<" has been swapped out"<<endl;
            }
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
    optimal();
}