#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

template <typename T>
void nth(T* arr, size_t len, size_t k) {
    assert(len > k);
    static default_random_engine eng{static_cast<size_t>(
        chrono::steady_clock::now().time_since_epoch().count())};
    uniform_int_distribution<size_t> d(0, len - 1);
    size_t rand_idx{d(eng)};
    swap(arr[0], arr[rand_idx]);
    const T& x = arr[0];
    int l = 1, r = len - 1;
    while (true) {
        while (l <= r && arr[l] <= x) {
            ++l;
        }
        while (l <= r && arr[r] >= x) {
            --r;
        }
        if (l > r) {
            break;
        }
        swap(arr[l++], arr[r--]);
    }
    swap(arr[0], arr[r]);
    if (r < k) {
        nth(arr + l, len - l, k - l);
    } else if (r > k) {
        nth(arr, r, k);
    }
}

void test(size_t n, size_t m) {
    vector<int> arr(n);
    iota(arr.rbegin(), arr.rend(), 0);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    nth(arr.data(), arr.size(), m);

    for (int i = 0; i <= m; ++i) {
        cout << arr[i] << " ";
    }
    cout << "| ";
    for (int i = m + 1; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    assert(argc == 3);
    size_t n = static_cast<size_t>(stoi(argv[1]));
    size_t m = static_cast<size_t>(stoi(argv[2]));
    test(n, m);

    return 0;
}