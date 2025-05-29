#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void taskA(){
    for (int i = 0; i < 10; ++i){
        // set a sleep time
        sleep(1);
        printf("TaskA: %d\n", i);
        // do not buffer
        fflush(stdout);
    }
}

void taskB(){
    for (int i = 0;i < 10; ++i){
        // set a sleep time
        sleep(1);
        printf("TaskB: %d\n", i);
        // do not buffer
        fflush(stdout);
    }
}

int main(){
    // create two threads
    thread t1(taskA);
    thread t2(taskB);

    // wait for the threads to finish or prevent the main thread from exiting
    t1.join();
    t2.join();
    return 0;
}