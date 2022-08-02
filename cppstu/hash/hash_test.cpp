#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using pii = pair<int, int>;

struct Hash {
    int operator()(const pii& p) {
        return hash<int>()(p.first * 233 + p.second);
    }
};

int main() {
    auto hpii = [](const pii& p) { return hash<int>()(p.first * 233 + p.second); };

    unordered_map<pii, int, Hash> ump;


    return 0;
}