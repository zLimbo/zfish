#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

#include "skiplist.hpp"
using namespace std;

int main() {
    SkipList<int> skl;
    map<int, int> mp;
    int n = 10000000;
    for (int i = 0; i < n; ++i) {
        ++mp[skl.RandomLevel()];
    }

    for (auto [k, v] : mp) {
        printf("%2d: %7.6f\n", k, static_cast<double>(v) / n);
    }

    return 0;
}