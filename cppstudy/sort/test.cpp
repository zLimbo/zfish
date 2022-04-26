
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <iostream>
#include <chrono>
#include <cassert>

using namespace std;

void print(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void quick_sort(vector<int>& arr, int l, int r) {
    if (r - l <= 1) return;
    static default_random_engine e;
    uniform_int_distribution<int> u(l, r - 1);
    swap(arr[l], arr[u(e)]);
    int x = arr[l];
    int L = l + 1, R = r - 1;
    while (true) {
        while (L <= R && arr[L] <= x) ++L;
        while (L <= R && arr[R] >= x) --R;
        if (L > R) break;
        swap(arr[L++], arr[R--]);
    }
    swap(arr[l], arr[R]);
    quick_sort(arr, l, R);
    quick_sort(arr, L, r);
}

// void quick_sort(vector<int>& arr, int l, int r) {
//     if (r - l <= 1) return;
// }

void TestQuickSort(int k, int n) {
    while (k--) {
        vector<int> arr(n);

        static random_device r;
        static default_random_engine e(r());
        static uniform_int_distribution<int> u(0);

        for (int i = 0; i < n; ++i) {
            arr[i] = u(e);
        }

        // print(arr);

        quick_sort(arr, 0, arr.size());

        // print(arr);
        // printf("\n");

        for (size_t i = 1; i < arr.size(); ++i) {
            assert(arr[i - 1] <= arr[i]);
        }
    }
}

int main() {
    auto before = chrono::steady_clock::now();
    TestQuickSort(1e1, 1e1);
    auto take = chrono::duration_cast<chrono::duration<double>>(
        chrono::steady_clock::now() - before);
    cout << "take " << take.count() << " s" << endl;

    return 0;
}