
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <signal.h>
#include <sstream>
using namespace std;

class Stream {
public:
    using self = Stream;
    Stream(const char* file, int line) { ss << file << " " << line << " |"; };

    template <typename T>
    self& operator<<(T&& x) {
        ss << x;
        return *this;
    }

    ~Stream() {
        string s = ss.str();
        printf("msg={%s} len=%ld\n", s.data(), s.length());
    }

private:
    stringstream ss;
};

#define Log Stream(__FILE__, __LINE__)

int main() {
    int x = 10;
    double y = 20.5;
    Log << x << y << " "
        << "abcdeft"
        << " " << true;
    Log << x << y << " "
        << "abcdeft"
        << " " << true;

    printf("ok\n");

    return 0;
}