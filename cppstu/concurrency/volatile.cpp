
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

// volatile int x = 0;

int main() {
    atomic<int> x;

    x++;

    return 0;
}

// volatile int sum1 = 0;
// int sum2 = 0;

// void func(int num) {
//     for (int i = 0; i < num; ++i) {
//         sum1 += 10;
//         sum2 += 10;
//     }
// }

// int main() {
//     int num = 100000;

//     thread t1{func, num};
//     thread t2{func, num};

//     int sum3 = 0;
//     for (int i = 0; i < num * 2; ++i) {
//         sum3 += 10;
//     }

//     t1.join();
//     t2.join();

//     printf("sum1 = %d\nsum2 = %d\nsum3 = %d\n", sum1, sum2, sum3);
//     // assert(sum == 100 * 10 * 2);

//     return 0;
// }