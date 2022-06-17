#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <cmath>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

int main() {
    default_random_engine e;
    uniform_real_distribution<double> u(0, 10);
    for (int i = 0; i < 10; ++i) {
        cout << u(e) << endl;
        this_thread::sleep_for(chrono::milliseconds{20});
    }

    cout << acos(-1) << endl;

    return 0;
}
