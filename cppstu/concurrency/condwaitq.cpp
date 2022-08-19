#include <pthread.h>
#include <unistd.h>

#include <algorithm>
#include <bitset>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

thread_local int tid;
mutex mu;
condition_variable cond1, cond2;

constexpr int LEN = 100 * 100;
bitset<100 * 100> bst;

void func(int id, condition_variable &cond) {
    tid = id;
    printf("%d start\n", tid);
    unique_lock<mutex> lock(mu);
    cond.wait(lock);
    printf("%d end\n", tid);
}

int main() {
    thread t1(func, 1, ref(cond1));
    thread t2(func, 2, ref(cond1));
    thread t3(func, 3, ref(cond2));

    sleep(1);

    cond1.notify_one();

    cond1.notify_one();

    cond2.notify_one();

    t1.join();
    t2.join();
    t3.join();

    return 0;
}