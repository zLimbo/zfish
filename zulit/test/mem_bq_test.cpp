
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../memory_blocking_queue.hpp"
using namespace std;

class A {
public:
    int x_;
    A(int x) : x_(x) {}
    int memorySize() const {
        return x_;
    }
};

int main() {
    MemoryBlockingQueue<A> mem_bq{1024};

    thread t1{[&] {
        for (int i = 0; i < 1000; ++i) {
            printf("t1 put %d, mem_bq size: %ld, mem size: %ld\t=>\n", i,
                   mem_bq.size(), mem_bq.memorySize());
            mem_bq.enqueue(i);
            this_thread::sleep_for(chrono::milliseconds{200});
        }
    }};

    thread t2{[&] {
        for (;;) {
            A x = mem_bq.dequeue();
            printf("t2 get %d, mem_bq size: %ld, mem size: %ld\t<=\n", x.x_,
                   mem_bq.size(), mem_bq.memorySize());
            this_thread::sleep_for(chrono::seconds{1});
        }
    }};

    t1.join();
    t2.join();
    return 0;
}