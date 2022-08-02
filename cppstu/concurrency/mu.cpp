#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

int main() {
    timed_mutex tmu;

    auto fut1 = async(launch::async, [&]() {
        // this_thread::sleep_for(chrono::seconds{1});
        unique_lock<timed_mutex> lock(tmu, try_to_lock);
        if (lock.owns_lock()) {
            cout << "owns_lock" << endl;
        } else {
            cout << "no lock" << endl;
        }
    });

    {
        unique_lock<timed_mutex> lock(tmu);
        this_thread::sleep_for(chrono::seconds{1});
    }

    fut1.get();

    return 0;
}