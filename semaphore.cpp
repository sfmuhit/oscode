#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int s = 1;  // Semaphore variable

void wait() {
    while(s <= 0) {
        // Busy wait
    }
    s--;
}

void signal() {
    s++;
}

void critical_section(int id) {
    wait();
    cout << "Thread " << id << " is in critical section" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Thread " << id << " is leaving" << endl;
    signal();
}

int main() {
    thread t1(critical_section, 1);
    thread t2(critical_section, 2);
    
    t1.join();
    t2.join();
    
    return 0;
}