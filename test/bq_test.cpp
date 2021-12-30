#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../hlib/zfish.hpp"
using namespace std;

struct Obj {
    Obj() {}
    Obj(int x, int y) { printf("x=%d, y=%d\n", x, y); }
    Obj(const Obj& o) { cout << "[copy] Obj(const Obj& o)" << endl; }
    Obj(Obj&& o) { cout << "[move] Obj(Obj&& o)" << endl; }
    Obj& operator=(const Obj& o) {
        cout << "[copy] operator=(const Obj& o)" << endl;
        return *this;
    }
    Obj& operator=(Obj&& o) {
        cout << "[move] Obj& operator=(Obj&& o)" << endl;
        return *this;
    }
};

void producer(zfish::BlockingQueue<Obj>& bq, int num = 100) {
    for (int i = 0; i < num; ++i) {
        // bq.enqueue(string("x" + to_string(i)));
        bq.enqueue(i, i);
        printf("[producer] produce one, count=%d\n", i + 1);
        this_thread::sleep_for(chrono::seconds(3));
    }
}

void consumer(zfish::BlockingQueue<Obj>& bq) {
    int cnt = 0;
    while (true) {
        Obj x = bq.dequeue();
        printf("[consumer] consume one, count=%d\n", ++cnt);
    }
}

int main() {

    zfish::BlockingQueue<Obj> bq(5);

    vector<thread> ths;

    ths.emplace_back([&] { producer(bq); });
    ths.emplace_back([&] { consumer(bq); });

    for (auto& th : ths) th.join();

    return 0;
}