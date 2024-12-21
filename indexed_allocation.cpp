#include<iostream>
#include<vector>
#include<map>

using namespace std;

int block_size;
const int disk_size = 20;
int empty_blocks = 0;
int num_files = 0;
map<string, pair<int, int> > directory;
vector<bool> disk_avail(disk_size, false);
vector<pair<string, int> > disk(disk_size);
vector<vector<int> > index_table;

class file{
    public:
    string file_name;
    int file_size;
    int partitions;

    file() {};
    file(string &fname, int fsize) : file_name(fname), file_size(fsize) {
        partitions = (file_size + block_size - 1)/block_size;
    };
};

void initialize(){
    cout<<"Enter block size: "; cin>>block_size;
    cout<<"Enter number of empty blocks: "; cin>>empty_blocks;
    cout<<"Enter indices of empty blocks: ";
    for(int i = 0; i < empty_blocks; i++){
        int x; cin>>x;
        disk_avail[x] = true;
    }
}

void indexed_file_allocation(){
    cout<<"Enter number of files: "; cin>>num_files;
    for(int i = 0; i < num_files; i++){
        string fname; int fsize;
        cout<<"Enter file name: "; cin>>fname;
        cout<<"Enter file size: "; cin>>fsize;
        file f(fname, fsize);
        int avail = 0;
        for(int j = 0; j < disk_size; j++){
            if(disk_avail[j]) avail++;
            if(avail >= f.partitions) break;
        }
        if(avail >= f.partitions){
            directory[f.file_name] = make_pair(index_table.size(), f.file_size);
            vector<int> index_table_entry; int count = 0;
            for(int j = 0; count < f.partitions; j++){
                if(disk_avail[j]){
                    disk_avail[j] = false;
                    disk[j] = make_pair(f.file_name, count + 1);
                    index_table_entry.push_back(j);
                    count++;
                }
            }
            index_table.push_back(index_table_entry);
            cout<<"File "<<f.file_name<<" has been allocated successfully"<<endl;
        }
        else{
            cout<<"File "<<f.file_name<<" could not be allocated"<<endl;
        }
    } 
}

void display_directory(){
    for(pair<string, pair<int, int> > entry: directory){
        string fname = entry.first; int file_index = entry.second.first;
        int fsize = entry.second.second;
        cout<<"File Name: "<<fname<<endl;
        cout<<"File Size: "<<fsize<<endl;
        cout<<"Memory Block\tFile\t\tPartition"<<endl;
        int fpartitions = index_table[file_index].size();
        for(int j = 0; j < fpartitions; j++){
            int block = index_table[file_index][j];
            cout<<block<<"\t\t"<<disk[block].first<<"\t\t"<<disk[block].second<<endl;
        }
        cout<<endl;
    }
}

int main(){
    initialize();
    indexed_file_allocation();
    display_directory();
}
