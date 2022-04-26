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
    if (ump[k].count(y) && ump[k][y].first >= x) {
        return ump[k][y].second;
    }
    int p = y + vb[k] < 0 ? 0 : dfs(k - 1, x + va[k], y + vb[k], va, vb);
    int q = dfs(k - 1, x, y, va, vb);
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
    return dfs(n - 1, x, y, va, vb);
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
        int a = rand() % 1000;
        int b = rand() % 1000;
        if (a < b) {
            swap(a, b);
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

int test(int n) {
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
                    chrono::steady_clock::now() - before)
                    .count();

    auto before1 = chrono::steady_clock::now();
    int res1 = solve1(n, va, vb);
    auto take1 = chrono::duration_cast<chrono::milliseconds>(
                     chrono::steady_clock::now() - before1)
                     .count();

    printf(
        "n: %3d, res: %10d, take: %10ld ms, res1: %10d, take1: %10ld ms, "
        "%10.2f\n",
        n, res, take, res1, take1, (double)take1 / take);

    if (res != res1) {
        return -1;
    }

    // printf("n: %3d, res: %10d, take: %10ld ms\n", n, res, take);

    return 0;
}

int main() {
    srand(time(0));
    for (int i = 0; i <= 10000; ++i) {
        // printf("i:%5d, ", i);
        if (test(i) == -1) {
            printf("error\n");
            break;
        }
    }
    printf("success\n");
}