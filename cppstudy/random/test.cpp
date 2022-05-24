
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <random>
#include <numeric>

using namespace std;

int main() {
    mt19937 gen{random_device{}()};
    uniform_int_distribution<int> d(1, 10);

    for (int i = 0; i < 10; ++i) {
        cout << d(gen) << endl;
    }
    numeric_limits<double>::max();

    return 0;
}