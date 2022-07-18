// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
#include <unordered_map>
#include <unordered_set>
#include <cmath>

int gcd(int x, int y) {
    return x % y == 0 ? y : gcd(y, x % y);
}

constexpr long long maxn = 100000000;

int solution(vector<Point2D> &A) {
    // write your code in C++14 (g++ 6.2.0)

    unordered_map<int, unordered_map<int, unordered_map<int, unordered_set<int>>>> ump;
    unordered_map<int, unordered_set<int>> row, col;

    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int dx = A[i].x - A[j].x, dy = A[i].y - A[j].y;
            if (dx == 0) {
                col[A[i].x].insert(i);
                col[A[i].x].insert(j);
            } else if (dy == 0) {
                row[A[i].y].insert(i);
                row[A[i].y].insert(j);
            } else {
                int a = abs(dx), b = abs(dy);
                int gd = a > b ? gcd(a, b) : gcd(b, a);
                a /= gd;
                b /= gd;
                if (dx * dy > 0) {
                    a = -a;
                }
                int c = b * A[i].x + a * A[i].y;
                auto& up = ump[a][b][c];
                up.insert(i);
                up.insert(j);
            }
        }
    }

    long long res = 0;
    bool debug = false;
    
    for (auto& p1: ump) {
        int a = p1.first;
        for (auto& p2: p1.second) {
            int b = p2.first;
            for (auto& p3: p2.second) {
                int c = p3.first;
                auto& us = p3.second;
                long long x = us.size();
                if (x >= 3) {
if (debug) cout << a << " " << b << " " << c << " " << x << endl;
                    res += x * (x - 1) * (x - 2) / 6;
                    if (res > maxn) {
                        return -1;
                    }
                }
            }
        }
    }

    for (auto& p: row) {
        int k = p.first;
        auto& us = p.second;
        long long x = us.size();
        if (x >= 3) {
if (debug) cout << "row " << k << " "  << x << endl;
            res += x * (x - 1) * (x - 2) / 6;
            if (res > maxn) {
                return -1;
            }
        }
    }

    for (auto& p: col) {
        int k = p.first;
        auto& us = p.second;
        long long x = us.size();
        if (x >= 3) {
if (debug) cout << "col " << k << " " << x << endl;
            res += x * (x - 1) * (x - 2) / 6;
            if (res > maxn) {
                return -1;
            }
        }
    }
    

    return res;
}


int main() {

    

    return 0;
}