
#include <iostream>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <cmath>
#include <chrono>

using namespace std;

void now1() {
    time_t now = time(nullptr);
    cout << "Now is: " << ctime(&now);
}

void now2() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    cout << "Now is: " << ctime(&time) << endl;
}

void diff1() {
    time_t before = time(0);
    double sum = 0;
    for (int i = 0; i < 1e9; ++i) {
        sum += sqrt(i);
    }
    time_t after = time(0);
    double take = difftime(after, before);
    printf("%fs\n", take);
}

void diff2() {
    auto before = chrono::system_clock::now();
    double sum = 0;
    for (int i = 0; i < 1e9; ++i) {
        sum += sqrt(i);
    }
    auto after = chrono::system_clock::now();
    using Seconds = chrono::duration<double>;
    double take = chrono::duration_cast<Seconds>(after - before).count();
    printf("%fs\n", take);
}

int main() {
    now1();
    now2();

    diff1();
    diff2();

    return 0;
}