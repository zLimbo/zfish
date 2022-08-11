#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <tuple>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> presum(n + 1);
        int res = -1;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            presum[i + 1] = presum[i] + x;
        }
        
        priority_queue<tuple<int, int, int>> pq;
        for (int i = n; i > 0; --i) {
            pq.emplace(presum[i] - presum[0], i, 0);
        }
        while (!pq.empty()) {
            int x, y, z;
            tie(x, y, z) = pq.top(); pq.pop();
            if (x % k) {
                cout << x << endl;
                break;
            }
            if (z + 1 < y) {
                pq.emplace(presum[y] - presum[z + 1], y, z + 1);
            }
        }
    }
    
    return 0;
}