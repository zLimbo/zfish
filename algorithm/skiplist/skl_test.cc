#include <chrono>
#include <random>
#include <unordered_set>

#include "skiplist.hpp"

using namespace std;

using namespace zfish;

int main() {
    zfish::SkipList<int> skl;

    int n = 1000000;
    int m = 100000;

    mt19937 eng;
    uniform_int_distribution<int> d(0, n);

    unordered_set<int> us;
    int count = 0;

    auto before = chrono::steady_clock::now();
    auto t1 = 0ms, t2 = 0ms;
    for (int i = 0; i < n; ++i) {
        int x = d(eng);

        before = chrono::steady_clock::now();
        us.insert(x);
        auto take1 = chrono::steady_clock::now() - before;

        bool ok = skl.Insert(x);

        count += (int)ok;
    }

    for (int i = 0; i < m; ++i) {
        int x = d(eng);
        us.erase(x);
        count -= skl.Erase(x);
    }

    // skl.Print();
    cout << "skl size: " << skl.Size() << endl;
    cout << "set size: " << us.size() << endl;

    return 0;
}