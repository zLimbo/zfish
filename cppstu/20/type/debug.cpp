#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace fmt;

template <typename T>
struct [[deprecated]] dump {};

int main() {
    unordered_map<int, int> mp;
    dump<decltype(mp)> d;

    return 0;
}
