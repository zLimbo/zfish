#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

int main() {
    std::array<int, 1000> values;
    std::fill(begin(values), end(values), 6);

    fmt::println("before: {}", values);

    std::sort(begin(values), end(values), [](int v1, int v2) { return v1 > v2; });

    fmt::println("after: {}", values); 

    return 0;
}