
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n);
    vector<int> vis(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    vector<pair<int, int>> B(n - 1);
    for (int i = 0; i < n; ++i) {
        B[i] = {A[i], i};
    }
    sort(B.begin(), B.end());
    int up = A[n - 1];

    int res = 0;

    for (int i = B.size() - 1; i >= 0; --i) {
        int x = B[i].first, y = B[i].second;
        if (x < up) {
            break;
        }
        bool ok = false;
        for (int j = 0; j < i; ++j) {
            if (B[j].first < x && B[j].second < y && !vis[B[j].second] && m >= B[j].first) {
                res += x - B[j].first;
                m -= B[j].first;
                ok = true;
                vis[B[j].second] = 1;
                break;
            }
        }
    }

    for (int j = 0; j < )



    return 0;
}