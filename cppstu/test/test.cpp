#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;

struct A {
    void f() {
        auto y = x;
        thread t1{[y]() { cout << "y = " << y << endl; }};
    }

    shared_ptr<int> x;
};

int main() {
    A a;
    a.f();

    return 0;
}