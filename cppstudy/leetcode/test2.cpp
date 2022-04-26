#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <limits>
#include <chrono>
#include <cassert>

using namespace std;

unordered_map<int, unordered_map<int, pair<int, int>>> ump;
int dfs(int k, int x, int y, vector<int>& va, vector<int>& vb) {
    if (k == -1) {
        if (x < 0) {
            return 0;
        }
        return x + y;
    }
    if (ump[k][y].first && ump[k][y].first >= x) {
        return ump[k][y].second;
    }
    if (y + vb[k] < 0) {
        return dfs(k - 1, x, y, va, vb);
    }
    int p = dfs(k - 1, x, y, va, vb);
    int q = dfs(k - 1, x + va[k], y + vb[k], va, vb);
    return (ump[k][y] = {x, max(p, q)}).second;
}

int solve(int n, vector<int> va, vector<int> vb) {
    ump.clear();
    int x = 0;
    int y = 0;
    for (int i = 0; i < n; ++i) {
        if (vb[i] > 0) {
            x += va[i];
            y += vb[i];
            va[i] = -va[i];
            vb[i] = -vb[i];
        }
    }
    return max(0, dfs(n - 1, x, y, va, vb));
}

int dfs1(int k, int x, int y, vector<int>& va, vector<int>& vb) {
    if (k == -1) {
        if (x < 0 || y < 0) {
            return -1;
        }
        return 0;
    }
    int p = dfs1(k - 1, x, y, va, vb);
    int q = dfs1(k - 1, x + va[k], y + vb[k], va, vb);
    if (q != -1) {
        q += va[k] + vb[k];
    }
    return max(p, q);
    // return max(dfs1(k - 1, x, y, va, vb),
    //            va[k] + vb[k] + dfs1(k - 1, x + va[k], y + vb[k], va, vb));
}

int solve1(int n, vector<int> va, vector<int> vb) {
    return max(0, dfs1(n - 1, 0, 0, va, vb));
}

int gen_loop_n = 0;

void gen(int n, vector<int>& va, vector<int>& vb) {
    ++gen_loop_n;
    int pre_a = 0;
    int pre_b = 0;
    for (int i = 0; i < n; ++i) {
        int a = rand() % 102 + 2;
        int b = rand() % 102 + 2;
        if (a < b) {
            swap(a, b);
        } else if (a == b) {
            a += 1;
            b -= 1;
        }
        b = -b;

        if (rand() % 2) {
            swap(a, b);
        }

        if (pre_a < 0) {
            swap(a, b);
        }
        pre_a += a;
        pre_b += b;

        va[i] = a;
        vb[i] = b;
    }
    if (pre_a < 0 || pre_b < 0) {
        // cout << pre_a << " " << pre_b << endl;
        return gen(n, va, vb);
    }
}

int test() {
    int n = 30;
    // cin >> n;

    vector<int> va(n);
    vector<int> vb(n);

    gen(n, va, vb);

    // va = {-18, -24, 89, 24};
    // vb = {21, 96, -88, 0};

    // printf("gen %d times, data:\n", gen_loop_n);
    // for (int i = 0; i < n; ++i) {
    //     printf("[%d, %d] ", va[i], vb[i]);
    // }
    // printf("\n");

    auto before = chrono::steady_clock::now();
    int res = solve(n, va, vb);
    auto take = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - before);
    // printf("res: %d, take: %ld ms\n", res, take.count());

    auto before1 = chrono::steady_clock::now();
    int res1 = solve1(n, va, vb);
    auto take1 = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - before1);

    printf("res: %d, take: %ld ms, res1: %d, take1: %ld ms, ok\n", res,
           take.count(), res1, take1.count());

    // assert(res == res1);
    if (res != res1) {
        return -1;
    }
    return 0;
}

int main() {
    srand(time(0));
    for (int i = 0; i < 100; ++i) {
        if (test() == -1) {
            printf("error\n");
        }
    }
    printf("success\n");
}