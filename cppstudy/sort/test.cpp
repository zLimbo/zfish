
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <iostream>
#include <chrono>
#include <cassert>
#include <map>

#include "sort_test.hpp"

using namespace std;

int main() {
    zfish::sortFuncTest<int>(zfish::quick_sort::V1<int>(), 1e5, 1, -1e5, 1e5);

    zfish::SortTest<int> sortTest(1e5, 1, -1e5, 1e5);

    sortTest.add<zfish::quick_sort::V1<int>>();
    sortTest.add<zfish::quick_sort::V2<int>>();

    sortTest.test();

    return 0;
}

// if (r - l <= 1) return;
//     std::uniform_int_distribution<size_t> u(l, r - 1);
//     swap(arr[l], arr[u(e)]);
//     T x = arr[l];
//     size_t L = l + 1, R = r - 1;
//     while (true) {
//         while (L <= R && arr[L] <= x) ++L;
//         while (L <= R && arr[R] >= x) --R;
//         if (L > R) break;
//         swap(arr[L++], arr[R--]);
//     }
//     swap(arr[l], arr[R]);
//     v1(arr, l, R);
//     v1(arr, L, r);