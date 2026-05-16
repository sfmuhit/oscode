#include <iostream>
#include <thread>
#include <queue>
#include <semaphore>
using namespace std;

queue<int> b;
counting_semaphore<5> e(5), f(0);
binary_semaphore m(1);

void p(int id) {
    for(int i=1;;i++) {
        e.acquire(); m.acquire();
        b.push(i);
        cout<<"P"<<id<<" produced: "<<i<<endl;
        m.release(); f.release();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void c(int id) {
    while(1) {
        f.acquire(); m.acquire();
        int x=b.front(); b.pop();
        cout<<"C"<<id<<" consumed: "<<x<<endl;
        m.release(); e.release();
        this_thread::sleep_for(chrono::milliseconds(800));
    }
}

int main() {
    thread(p,1).detach(); thread(p,2).detach(); thread(c,1).join();
}