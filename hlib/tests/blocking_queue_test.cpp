#include "../blocking_queue.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;

int main() {
    BlockingQueue<int> bq;
    thread th1{[&] {
        for (int i = 0; i < 100; ++i) {
            bq.enqueue(i);
            printf("enqueue %d\n", i);
            // this_thread::sleep_for(chrono::milliseconds{rand() % 10});
        }
    }};

    thread th2{[&] {
        for (int i = 0; i < 100; ++i) {
            int x = bq.dequeue();
            printf("dequeue %d\n", x);
        }
    }};

    th1.join();
    th2.join();

    return 0;
}