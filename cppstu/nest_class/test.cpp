
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <future>
#include <thread>
// #include <bits/stdc++.h>

using namespace std;

int main() {
    int a = 1;
    struct {
        int operator()(int x) {
            cout << "x=" << x << endl;
            return x;
        }
    } nest;
    auto y = std::async(nest, 5);
    cout << "nest.ret=" << y.get() << endl;
    return 0;
}