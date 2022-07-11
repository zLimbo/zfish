
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct T {
    char ch;
    int cnt = 0;
    int num;
};

int main() {
    string ls, rs;

    getline(cin, ls);
    cin >> rs;

    istringstream sin(ls);
    vector<string> vs;
    string tmp;
    while (sin >> tmp) {
        vs.push_back(tmp);
    }

    unordered_map<char, T> lump, rump;

    for (string& s : vs) {
        int base = 1;
        for (int i = s.size() - 1; i >= 0; --i) {
            lump[s[i]].cnt += base;
            base *= 10;
        }
    }

    {
        int base = 1;
        for (int i = rs.size() - 1; i >= 0; --i) {
            lump[rs[i]].cnt += base;
            base *= 10;
        }
    }

    if (lump.size() != rump.size()) {
        printf("0\n");
        return 0;
    }

    for (auto p : lump) {
        if (!rump.count(p.first)) {
            printf("0\n");
            return 0;
        }
    }

    for (auto p: lump) {
        
    }

    return 0;
}