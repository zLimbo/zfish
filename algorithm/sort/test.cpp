
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <iostream>
#include <chrono>
#include <cassert>
#include <map>

#include "sort_test.hpp"
#include "quick_sort.hpp"
#include "insert_sort.hpp"
#include "bubble_sort.hpp"
#include "select_sort.hpp"
#include "shell_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"

using namespace std;

int main() {
    zfish::SortTest<int> sortTest(1e4, -1e3, 1e3);

    sortTest.add<zfish::quick_sort::V11<int>>();
    sortTest.add<zfish::quick_sort::V12<int>>();
    sortTest.add<zfish::quick_sort::V13<int>>();
    sortTest.add<zfish::quick_sort::V14<int>>();
    sortTest.add<zfish::quick_sort::V15<int>>();

    sortTest.add<zfish::merge_sort::V1<int>>();

    sortTest.add<zfish::heap_sort::V1<int>>();

    sortTest.add<zfish::quick_sort::V21<int>>();
    sortTest.add<zfish::quick_sort::V22<int>>();

    sortTest.add<zfish::insert_sort::V1<int>>();
    sortTest.add<zfish::insert_sort::V2<int>>();
    sortTest.add<zfish::bubble_sort::V1<int>>();
    sortTest.add<zfish::select_sort::V1<int>>();

    sortTest.add<zfish::shell_sort::V1<int>>();
    sortTest.add<zfish::shell_sort::V2<int>>();

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