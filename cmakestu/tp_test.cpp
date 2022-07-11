#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "hlib/zfish.hpp"
#include <chrono>

using namespace std;

template <typename T>
void print(T&& s) {
    this_thread::sleep_for(chrono::seconds{1});
    printf("%c: %p\n", s[0], s.data());
}

void f1() {
    this_thread::sleep_for(chrono::seconds{1});
    cout << "f1" << endl;
}

void f2(int x) {
    this_thread::sleep_for(chrono::seconds{1});
    cout << "f2"
         << " " << x << endl;
}

int f3() {
    this_thread::sleep_for(chrono::seconds{1});
    cout << "f3" << endl;
    return 3;
}

int main() {
    zfish::ThreadPool pool(4);

    pool.put(f1);
    pool.put(f2, 5);
    auto res = pool.put(f3);
    auto res2 = pool.put([] { return 5.5; });

    int f3res = res.get();
    double f4res2 = res2.get();

    cout << "f3res: " << f3res << endl;
    cout << "res2: " << f4res2 << endl;

    return 0;
}