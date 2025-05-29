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

    // Initial time
    int time = 0;
    // pointer for inserting the processes arrived till time
    int j = 1;
    // min heap for having the highest priority on the top {priority,index}
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    // pushing the first process onto the heap
    pq.push({processes[0].priority,0});

    // maintaining initial_time for printing the ganntChart
    int initial_time = processes[0].arrival_time;
    // storing the ganntChartInfo
    vector<vector<int>> ganntChartInfo;

    while(!pq.empty()){
        // get the process with the highest priority from the heap
        int index = pq.top().second;
        pq.pop();
        processes[index].remaining_time--;
        time++;

        // printing the ganntChart
        // cout<<"| "<<initial_time<<" "<<"(Process "<<processes[index].process_id<<")"<<" "<<time<<" |"<<endl;
        ganntChartInfo.push_back({initial_time,processes[index].process_id,time});
        // updating the initial_time
        initial_time = time;

        // checking if the process is completed or not
        if(processes[index].remaining_time == 0){

            processes[index].set_completion_time(time);
            processes[index].set_turnaround_time(processes[index].completion_time - processes[index].arrival_time);
            processes[index].set_waiting_time(processes[index].turnaround_time - processes[index].burst_time);
        }else{
            // if the process is not completed then push it back into the heap
            pq.push({processes[index].priority,index});
        }

        // inserting those process which have arrived till time
        bool ideal = true;
        for(;j<processes.size() and processes[j].arrival_time <= time; ++j){
            pq.push({processes[j].priority,j});
            ideal = false;
        }

        // if ideal state then increase the time upto the next process arrival time
        if(pq.empty() and ideal and j != processes.size()){
            // cpu is in ideal state and printing the ganntChart
            // cout<<"| "<<initial_time<<" "<<"(CPU Idle)"<<" "<<processes[j].arrival_time<<" |"<<endl;
            ganntChartInfo.push_back({initial_time,-1,processes[j].arrival_time});
            // updating the initial_time
            initial_time = processes[j].arrival_time;

            time = time + (processes[j].arrival_time - time);
            for(;j<processes.size() and processes[j].arrival_time <= time; ++j){
                pq.push({processes[j].priority,j});
            }
        }
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

    // printing the ganntChartInfo
    cout << "\nGantt Chart Information:" << endl;
    for(int i=1;i<ganntChartInfo.size();++i){
        // cout<<ganntChartInfo[i][0]<<' '<<ganntChartInfo[i][1]<<' '<<ganntChartInfo[i][2]<<endl;
        if(ganntChartInfo[i][1] == ganntChartInfo[i-1][1]){
            ganntChartInfo[i][0] = ganntChartInfo[i-1][0];
            ganntChartInfo[i-1][1] = -99;
        }
    }

    for(int i=0;i<ganntChartInfo.size();++i){
        if(ganntChartInfo[i][1] != -99)
        cout<<ganntChartInfo[i][0]<<' '<<ganntChartInfo[i][1]<<' '<<ganntChartInfo[i][2]<<endl;
    }

    return 0;
}