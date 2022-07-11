
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono_literals;

int main() {
        auto hour = 2h;
    auto minute = 5min;
    auto second = 20s;

    auto t = hour + minute + second;

    auto take = chrono::duration_cast<chrono::seconds>(t);

    cout << take.count() << "s" << endl;

    return 0;
}