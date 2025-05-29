#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include <iomanip>
using namespace std;

class Process{
    public:
        int process_id;
        int arrival_time;
        int burst_time;
        int remaining_time;
        int completion_time = 0;
        int turnaround_time = 0;
        int waiting_time = 0;

        Process(int process_id=-1,int arrival_time=0,int burst_time=0){
            this->process_id = process_id;
            this->arrival_time = arrival_time;
            this->burst_time = burst_time;
            this->remaining_time = burst_time;
        }
        void set_completion_time(int completion_time){
            this->completion_time = completion_time;
        } 
        void set_turnaround_time(int turnaround_time){
            this->turnaround_time = turnaround_time;
        } 
        void set_waiting_time(int waiting_time){
            this->waiting_time = waiting_time;
        }
        int get_completion_time(){
            return completion_time;
        }
        int get_turnaround_time(){
            return turnaround_time;
        }
        int get_waiting_time(){
            return waiting_time;
        }
};

bool cmp(Process& p1, Process& p2){
    if(p1.arrival_time == p2.arrival_time){
        return p1.burst_time < p2.burst_time;
    } else{
        return p1.arrival_time < p2.arrival_time;
    }
}

void printCentered(const string& text, int width) {
    int padding = width - text.size();
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    cout << string(padLeft, ' ') << text << string(padRight, ' ');
}

void printLine() {
    cout << "+---------------+---------------+---------------+---------------------+---------------------+---------------+" << endl;
}

int main(){

    // Time Quantum
    int time_quantum;
    cout << "Enter time quantum: ";
    cin >> time_quantum;

    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    vector<Process> processes(n);

    for(int i=0;i<n;++i){
        int arrival_time;
        int burst_time;
        cout<<"Enter arrival_time and burst_time of "<<i<<" process: ";
        cin>>arrival_time>>burst_time;
        processes[i] = Process(i,arrival_time,burst_time);
    }

    // sort the processes on the basis of arrival time 
    sort(processes.begin(),processes.end(),cmp); 

    // Initail time is zero
    int time = 0;
    // Pointer for process insertion till time
    int j = 1;
    // queue for process scheduling
    queue<int> q;
    // inserting the first Process into the queue
    q.push(0);
    // maintaining initial_time for printing the ganntChart
    int initial_time = 0;

    while(!q.empty()){
        // get the process index from the queue
        int idx = q.front();
        q.pop();
        Process &curr = processes[idx];
        
        if(curr.remaining_time > time_quantum){
            time = time + time_quantum;
            curr.remaining_time = curr.remaining_time - time_quantum;
        }else{
            time = time + curr.remaining_time;
            curr.remaining_time = 0;
        }
        // printing the ganntChart
        cout<<"| "<<initial_time<<" "<<"(Process "<<processes[idx].process_id<<")"<<" "<<time<<" |"<<endl;
        // updating the initial_time
        initial_time = time;

        // Pushing those processes which have arrived till time
        bool ideal = true;
        for(; j< processes.size() and processes[j].arrival_time <= time ;++j){
            q.push(j);
            ideal = false;
        }

        // checking if there is an ideal state or not
        int new_time = time;
        if(ideal and j<processes.size()){
            // printing the ganntChart and updating the time to current process arrival time 
            cout<<"| "<<initial_time<<" "<<"CPU Ideal"<<" "<<processes[j].arrival_time<<" |"<<endl;
            new_time = processes[j].arrival_time;
            initial_time = new_time;
            q.push(j);
            j++;
        }


        // if the process is completely finished
        if(curr.remaining_time == 0){
            curr.set_completion_time(time);
            curr.set_turnaround_time(curr.completion_time - curr.arrival_time);
            curr.set_waiting_time(curr.turnaround_time - curr.burst_time);
        }else{
            q.push(idx);
        }
        
        // setting new_time to original time
        time = new_time;
    }

    // computing the average turnaround_time and waiting_time
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    for(int i=0;i<n;++i){
        total_turnaround_time = total_turnaround_time + processes[i].get_turnaround_time();
        total_waiting_time = total_waiting_time + processes[i].get_waiting_time();
    }

     // Print table header
    printLine();
    cout << "| ";
    printCentered("Process_ID", 13);
    cout << " | ";
    printCentered("Arrival_time", 13);
    cout << " | ";
    printCentered("Burst_time", 13);
    cout << " | ";
    printCentered("Completion_time", 19);
    cout << " | ";
    printCentered("Turnaround_time", 19);
    cout << " | ";
    printCentered("Waiting_time", 13);
    cout << " |" << endl;
    printLine();

    // Print table rows
    for(int i = 0; i < n; ++i) {
        cout << "| ";
        printCentered(to_string(processes[i].process_id), 13);
        cout << " | ";
        printCentered(to_string(processes[i].arrival_time), 13);
        cout << " | ";
        printCentered(to_string(processes[i].burst_time), 13);
        cout << " | ";
        printCentered(to_string(processes[i].completion_time), 19);
        cout << " | ";
        printCentered(to_string(processes[i].turnaround_time), 19);
        cout << " | ";
        printCentered(to_string(processes[i].waiting_time), 13);
        cout << " |" << endl;
        printLine();
    }

    return 0;
}
