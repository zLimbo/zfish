#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;

void f() {
    printf("pid: %d, tid: %d\n", getpid(), gettid());
    ofstream fout{"out"};
    while (1) {
        sleep(1);
        fout << "1" << endl;
    }
}

void test() {
    thread t1{f};
    sleep(1);
    t1.detach();
    printf("exit test\n");
}

int main() {
    test();
    printf("exit main\n");
    sleep(3);
    return 0;
}