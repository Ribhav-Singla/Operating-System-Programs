#include<iostream>
#include<vector>
#include<algorithm>
#include <iomanip>
#include <queue>
using namespace std;

class Process{
    public:
        int process_id;
        int queue_number;
        int arrival_time;
        int burst_time;
        int remaining_time;
        int completion_time = 0;
        int turnaround_time = 0;
        int waiting_time = 0;

        Process(int process_id=-1,int arrival_time=0,int burst_time=0,int queue_number = 1){
            this->process_id = process_id;
            this->arrival_time = arrival_time;
            this->burst_time = burst_time;
            this->remaining_time = burst_time;
            this->queue_number = queue_number;
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

void roundRobin(queue<int>& rrQueue,vector<Process>& processes,int time_quantum,int &initialTime,int &currTime){
    while (!rrQueue.empty()){
        int index = rrQueue.front();
        rrQueue.pop();
        Process &curr = processes[index];

        // check if the remaining time of the process less than the time quantum 
        if(curr.remaining_time <= time_quantum){
            currTime = currTime + curr.remaining_time;
            curr.remaining_time = 0;
        }else{
            currTime = currTime + time_quantum;
            curr.remaining_time = curr.remaining_time - time_quantum;

            // printing the ganntChart
            cout<<initialTime<<" ( Process "<<curr.process_id<<" ) "<<currTime<<endl;
            initialTime = currTime;
        }

        // if the process is completely finished
        if(curr.remaining_time == 0){
            curr.set_completion_time(currTime);
            curr.set_turnaround_time(curr.completion_time - curr.arrival_time);
            curr.set_waiting_time(curr.turnaround_time - curr.burst_time);

            // printing the ganntChart
            cout<<initialTime<<" ( Process "<<curr.process_id<<" ) "<<currTime<<endl;
            initialTime = currTime;

        }else{
            rrQueue.push(index);
        }
    }
}

void fcfs(queue<int>& fcfsQueue,queue<int>& rrQueue,vector<Process>& processes,int time_quantum,int &initialTime, int& currTime,int &index){
    while (!fcfsQueue.empty()){
        int index = fcfsQueue.front();
        fcfsQueue.pop();
        Process &curr = processes[index];
        // currTime = currTime + curr.remaining_time;

        for(int i=1;i<= curr.remaining_time;++i){
            // check if a rrQueue process is has come or not
            bool flag = 0;
            int j=0;
            while(j < processes.size() and processes[j].arrival_time <= currTime){
                if(processes[j].remaining_time and processes[j].queue_number == 1){
                    rrQueue.push(j);
                    flag = 1;
                }
                if(flag){
                    // print ganntChart as there is context switch
                    cout<<initialTime<<" ( Process "<<curr.process_id<<" ) "<<currTime<<endl;
                    // update the initial time
                    initialTime = currTime;
                    // start executing the roundRobin
                    roundRobin(rrQueue,processes,time_quantum,initialTime,currTime);            
                }
                j++;
            }
            currTime = currTime + 1;
        }
    
        int turnaround_time = currTime - curr.arrival_time;
        int waiting_time = turnaround_time - curr.remaining_time;
        curr.set_completion_time(currTime);
        curr.set_turnaround_time(turnaround_time);
        curr.set_waiting_time(waiting_time);
        // zero the remaining time of the process
        curr.remaining_time = 0;

        // printing the ganntChart
        cout<<initialTime<<" ( Process "<<curr.process_id<<" ) "<<currTime<<endl;
        initialTime = currTime;
    }
}

int main(){

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
        int queue_number;
        cout<<"Enter arrival_time, burst_time and queue_number of "<<i<<" process: ";
        cin>>arrival_time>>burst_time>>queue_number;
        processes[i] = Process(i,arrival_time,burst_time,queue_number);
    }

    // sort the processes on the basis of arrival time 
    sort(processes.begin(),processes.end(),cmp); 

    // rrQueue for the round robin queue - 1
    queue<int> rrQueue;
    // fcfsQueue for the first come first serve queue - 2
    queue<int> fcfsQueue;
    // currTime is zero
    int currTime = 0;
    int index = 0;
    // maintaining initial time for ganntChart
    int initialTime = 0;

    while(index < processes.size() || !rrQueue.empty() || !fcfsQueue.empty()){
        // Add processes to the queue as they arrive
        while (index < processes.size() and processes[index].arrival_time <= currTime) {
            if(processes[index].remaining_time == 0){
                ;
            }
            else if (processes[index].queue_number == 1) {
                rrQueue.push(index);
            } else {
                fcfsQueue.push(index);
            }
            index++;
        }
        
        // executing the rrQueue processes first
        if(!rrQueue.empty()){
           roundRobin(rrQueue,processes,time_quantum,initialTime,currTime);
        }

        // executing the fcfsQueue processes second
        if(!fcfsQueue.empty()){
            fcfs(fcfsQueue,rrQueue,processes,time_quantum,initialTime,currTime,index);
        }

        // If no process is ready, advance time to the next process arrival there is CPU Ideal State
        else if (index < processes.size()) {
            currTime = processes[index].arrival_time;
            // printing the ganntChart as there is CPU Ideal state
            cout<<initialTime<<" ( CPU Ideal State ) "<<currTime<<endl;
            initialTime = currTime;
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

    return 0;
}