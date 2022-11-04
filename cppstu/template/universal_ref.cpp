#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

using namespace std;

int fib(int x) {
    return x <= 1 ? x : fib(x - 1) + fib(x - 2);
}

auto timeFuncInvocation = [](auto&& func, auto&&... args) {
    using namespace chrono;
    using Seconds = duration<double>;
    auto start = system_clock::now();
    forward<decltype(func)>(func)(std::forward<decltype(args)>(args)...);
    auto take = duration_cast<Seconds>(system_clock::now() - start).count();
    take = static_cast<double>(static_cast<long long>(take * 100)) / 100.0;
    return take;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw runtime_error("argc < 2");
    }
    int x = stoi(argv[1]);
    auto take = timeFuncInvocation(fib, x);
    cout << take << "s" << endl;

    return 0;
}