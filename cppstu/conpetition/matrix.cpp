
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vvi getOne(vvi &mat) {
    int n = mat.size(), m = mat[0].size();
    int up = n, down = -1, left = m, right = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mat[i][j]) {
                up = min(up, i);
                down = max(down, i);
                left = min(left, j);
                right = max(right, j);
            }
        }
    }
    vvi one(down - up + 1, vi(right - left + 1));
    for (int i = up; i <= down; ++i) {
        for (int j = left; j <= right; ++j) {
            one[i - up][j - left] = mat[i][j];
        }
    }
    return one;
}

void show(vvi &mat, string info) {
    cout << info << endl;
    for (auto &row : mat) {
        for (int x : row) {
            cout << x << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    freopen("in", "r", stdin);
    int k;
    cin >> k;
    int n, m;
    cin >> n >> m;
    vvi mat(n, vi(m));
    int up = n, down = -1, left = m, right = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mat[i][j];
        }
    }
    auto one = getOne(mat);
    n = one.size(), m = one[0].size();

    vvi updown(n, vi(m));
    vvi leftright(n, vi(m));
    vvi rotate90(m, vi(n));
    vvi rotate180(n, vi(m));
    vvi rotate270(m, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x = one[i][j];
            updown[n - i - 1][j] = x;
            leftright[i][m - j - 1] = x;
            rotate90[j][n - i - 1] = x;
            rotate180[n - i - 1][m - j - 1] = x;
            rotate270[m - j - 1][i] = x;
        }
    }
    // show(mat, "mat");
    // show(one, "one");
    // show(updown, "updown");
    // show(leftright, "leftright");
    // show(rotate90, "90");
    // show(rotate180, "180");
    // show(rotate270, "270");

    vector<vvi> all = {one, updown, leftright, rotate90, rotate180, rotate270};

    for (int t = 1; t < k; ++t) {
        cin >> n >> m;
        vvi m2(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> m2[i][j];
            }
        }
        auto m2one = getOne(m2);
        // show(m2one, "m2one");
        bool same = false;
        for (auto &m1one : all) {
            if (m1one == m2one) {
                same = true;
                break;
            }
        }
        cout << (same ? "true" : "false") << endl;
    }

    return 0;
}