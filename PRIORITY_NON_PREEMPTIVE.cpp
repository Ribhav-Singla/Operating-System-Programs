// Lower the number higher the priority

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>
#include<iomanip>
using namespace std;

class Process{
    public:
        int process_id;
        int arrival_time;
        int burst_time;
        int remaining_time;
        int priority;
        int completion_time = 0;
        int turnaround_time = 0;
        int waiting_time = 0;

        Process(int process_id=-1,int arrival_time=0,int burst_time=0,int priority=0){
            this->process_id = process_id;
            this->arrival_time = arrival_time;
            this->burst_time = burst_time;
            this->remaining_time = burst_time;
            this->priority = priority;
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
        if(p1.priority == p2.priority){
            return p1.burst_time < p2.burst_time;
        } else{
            return p1.priority < p2.priority;
        }
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
    
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    vector<Process> processes(n);

    for(int i=0;i<n;++i){
        int arrival_time;
        int burst_time;
        int priority;
        cout<<"Enter arrival_time, burst_time and priority of "<<i<<" process: ";
        cin>>arrival_time>>burst_time>>priority;
        processes[i] = Process(i,arrival_time,burst_time,priority);
    }

    // sort the processes on the basis of arrival time 
    sort(processes.begin(),processes.end(),cmp);

    // computing the completion_time, turnaround_time and waiting_time of each process on the basis of priority
    int completion_time = processes[0].arrival_time;
    int index = 0;
    int remaining = n;

    while(remaining){

        // maintaining initial_time for printing the ganntChart
        int initial_time = completion_time;

        int arrival_time = processes[index].arrival_time;
        int burst_time = processes[index].burst_time;
        int priority = processes[index].priority;

        completion_time = completion_time + burst_time;
        int turnaround_time = completion_time - arrival_time;
        int waiting_time = turnaround_time - burst_time;
        processes[index].set_completion_time(completion_time);
        processes[index].set_turnaround_time(turnaround_time);
        processes[index].set_waiting_time(waiting_time);
        processes[index].remaining_time = 0;
        remaining =  remaining - 1;

        // printing the ganntChart
        cout<<"| "<<initial_time<<" "<<"(Process "<<processes[index].process_id<<")"<<" "<<completion_time<<" |"<<endl;

        // if no process is remaining then we should break
        if(!remaining){
            break;
        }

        // finding the next process and having the least priority and remaining_time != 0
        int min_priority = INT_MAX;
        int min_index = -1;
        for(int i=0;i<n;++i){
            if(processes[i].remaining_time != 0 and processes[i].arrival_time <= completion_time and processes[i].priority < min_priority){
                min_priority = processes[i].priority;
                min_index = i;
            }
        }

        if(min_index == -1 and remaining){
            // find the first process where remaining_time != 0 and there is CPU ideal state
            for(int i=0;i<n;++i){
                if(processes[i].remaining_time != 0){
                    min_index = i;

                    // printing the ganntChart
                    cout<<"| "<<completion_time<<" "<<"(Process "<<processes[min_index].process_id<<")"<<" "<<processes[i].arrival_time<<" |"<<endl;

                    // update the completion time
                    completion_time = processes[i].arrival_time;
                    break;
                }
            }

        }

        // updating the index
        index = min_index;
    }
    

    // computing the average turnaround_time and waiting_time
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    for(int i=0;i<n;++i){
        total_turnaround_time = total_turnaround_time + processes[i].turnaround_time;
        total_waiting_time = total_waiting_time + processes[i].waiting_time;
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