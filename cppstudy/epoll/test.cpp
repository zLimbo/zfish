#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <limits>

using namespace std;

using Second = chrono::duration<double>;

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    size_t i = 1;

    cout << numeric_limits<size_t>::max() << endl;

    // auto before = chrono::steady_clock::now();
    // while (i != 0) {
    //     if (++i % 1000000000 == 0) {
    //         auto take = chrono::duration_cast<Second>(
    //             chrono::steady_clock::now() - before);
    //         cout << i << " takes " << take.count() << " s" << endl;
    //     }
    // }

    return 0;
}

class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<pair<int, int>>> v25(n, vector<pair<int, int>>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cnt2 = 0, cnt5 = 0;
                int x = grid[i][j];
                while (x % 5 == 0) {
                    ++cnt5;
                    x /= 5;
                }
                while (x % 2 == 0) {
                    ++cnt2;
                    x /= 2;
                }
                v25[i][j] = {cnt2, cnt5};
            }
        }

        vector<vector<pair<int, int>>> U(n, vector<pair<int, int>>(m));
        vector<vector<pair<int, int>>> D(n, vector<pair<int, int>>(m));
        vector<vector<pair<int, int>>> L(n, vector<pair<int, int>>(m));
        vector<vector<pair<int, int>>> R(n, vector<pair<int, int>>(m));

        auto add = [](pair<int, int>& lhs, pair<int, int>& rhs) {
            lhs.first += rhs.first;
            lhs.second += rhs.second;
        };
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                R[i][j] = D[i][j] = v25[i][j];
                if (i > 0) {
                    add(R[i][j], R[i - 1][j]);
                }
                if (j > 0) {
                    add(D[i][j], D[i][j - 1]);
                }
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                L[i][j] = U[i][j] = v25[i][j];
                if (i < n - 1) {
                    add(L[i][j], L[i + 1][j]);
                }
                if (j < m - 1) {
                    add(U[i][j], U[i][j + 1]);
                }
            }
        }

        auto aux = [](pair<int, int>& lhs, pair<int, int>& rhs,
                      pair<int, int>& ree) {
            int cnt2 = lhs.first + rhs.first - ree.first;
            int cnt5 = lhs.second + rhs.second - ree.second;
            return min(cnt2, cnt5);
        };

        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // cout << i << "," << j << ": " << R[i][j] << " " << L[i][j] <<
                // " " << D[i][j] << " " << U[i][j] << endl;
                res = max(res, aux(L[i][j], U[i][j], v25[i][j]));
                res = max(res, aux(L[i][j], D[i][j], v25[i][j]));
                res = max(res, aux(R[i][j], U[i][j], v25[i][j]));
                res = max(res, aux(R[i][j], D[i][j], v25[i][j]));
            }
        }

        return res;
    }
};