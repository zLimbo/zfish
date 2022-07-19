#include "lru.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main() {
    LRUList<int> lru(10);
    vector<int> v;
    iota(v.begin(), v.end(), 0);
    for (int i = 0; i < 10; ++i) {
        lru.push(i);
    }

    lru.show();

    lru.push(5);
    lru.push(7);
    lru.push(4);

    lru.show();

    int x = lru.pop();

    lru.show();

    return 0;
}