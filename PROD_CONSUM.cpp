# include <iostream>
# include <queue>
using namespace std;

class semaphore{
    int S;

    public:
        void init(int x){
            S = x;
        }

        void wait(){
            S--;
        }

        void signal(){
            S++;
        }

        int val(){
            return S;
        }
};
int n;
queue<int> buffer;

semaphore buffer_lock, empty_buffers, full_buffers;

void set_buffer(){
    cout<<"Enter buffer size: "; cin>>n;
    buffer_lock.init(1);
    empty_buffers.init(n);
    full_buffers.init(0);
}

void producer(){
    if((buffer_lock.val() == 0) || (empty_buffers.val() == 0)){
        cout<<"Buffer is FULL"<<endl;
        return;
    }
    empty_buffers.wait();
    buffer_lock.wait();
    int x; cout<<"Enter item to produce: "; cin>>x;
    buffer.push(x); cout<<"Producer has produced item: "<<x<<endl;
    buffer_lock.signal();
    full_buffers.signal();
}

void consumer(){
    if((buffer_lock.val() == 0) || (full_buffers.val() == 0)){
        cout<<"Buffer is EMPTY"<<endl;
        return;
    }
    full_buffers.wait();
    buffer_lock.wait();
    int x = buffer.front(); buffer.pop();
    cout<<"Consumer has consumed item: "<<x<<endl;
    buffer_lock.signal();
    empty_buffers.signal();
}

int main(){
    set_buffer();
    cout<<"1. Producer"<<endl;
    cout<<"2. Consumer"<<endl;
    cout<<"3. Exit"<<endl;
    while(true){
        int choice; cout<<"Enter Choice: "; cin>>choice;
        if(choice == 1){
            producer();
        }
        else if(choice == 2){
            consumer();
        }
        else if(choice == 3){
            cout<<"Program Terminated"<<endl;
            return 0;
        }
        else{
            cout<<"Invalid Choice, Try Again"<<endl;
        }
    }
}