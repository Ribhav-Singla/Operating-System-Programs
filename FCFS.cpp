#include<iostream>
#include<vector>
#include<algorithm>
#include <iomanip>
using namespace std;

class Process{
    public:
        int process_id;
        int arrival_time;
        int burst_time;
        int completion_time = 0;
        int turnaround_time = 0;
        int waiting_time = 0;

        Process(int process_id=-1,int arrival_time=0,int burst_time=0){
            this->process_id = process_id;
            this->arrival_time = arrival_time;
            this->burst_time = burst_time;
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

    // arrays for storing the processes in ganntChart
    vector<int> ganntChart_process;
    vector<int> ganntChart_time;

    // computing the completion_time, turnaround_time and waiting_time of each process
    int completion_time = processes[0].arrival_time;
    // pushing the completion time in ganntChart_time
    ganntChart_time.push_back(completion_time);

    for(int i=0;i<n;++i){
        // initial Time for printing the ganntChart
        int initial_time = completion_time;

        int arrival_time = processes[i].arrival_time;
        int burst_time = processes[i].burst_time;
        // reset the completion_time to arrival_time because there is CPU ideal state
        if(arrival_time > completion_time){
            completion_time = arrival_time;

            // printing the ganntChart
            cout<<"| "<<initial_time<<" "<<"CPU Ideal"<<" "<<completion_time<<" |"<<endl;
            ganntChart_process.push_back(-1);
            ganntChart_time.push_back(completion_time);
            initial_time = completion_time;
        }
        completion_time = completion_time + burst_time;
        int turnaround_time = completion_time - arrival_time;
        int waiting_time = turnaround_time - burst_time;
        processes[i].set_completion_time(completion_time);
        processes[i].set_turnaround_time(turnaround_time);
        processes[i].set_waiting_time(waiting_time);

        // printing the ganntChart
        cout<<"| "<<initial_time<<" "<<"(Process "<<processes[i].process_id<<")"<<" "<<completion_time<<" |"<<endl;
        ganntChart_process.push_back(processes[i].process_id);
        ganntChart_time.push_back(completion_time);
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

    // printing the ganntChart array
    cout << "Gannt Chart Process:" << endl;
    for (int i = 0; i < ganntChart_process.size(); ++i) {
        cout << ganntChart_process[i]<<' ';
    }
    cout<<endl;

    cout << "Gannt Chart Time:" << endl;
    for (int i = 0; i < ganntChart_time.size(); ++i) {
        cout << ganntChart_time[i]<<' ';
    }

    return 0;
}