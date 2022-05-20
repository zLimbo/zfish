#ifndef SORT_TEST_H
#define SORT_TEST_H

#include <random>

#include <cassert>
#include <limits>
#include <memory>
#include <memory.h>

#include "sort_func_base.hpp"

namespace zfish {

using namespace std;
using Second = chrono::duration<double>;

static default_random_engine e;

template <typename T>
void print(T* arr, int l, int r) {
    for (int i = l; i < r; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T, typename F>
void sortUniformRandom(F&& sortFunc, size_t n, T l = numeric_limits<T>::min(),
                       T r = numeric_limits<T>::max()) {
    sortFunc.reset();
    T* arr = new T[n];
    uniform_int_distribution<T> u(l, r);
    for (int j = 0; j < n; ++j) {
        arr[j] = u(e);
    }
    SortFunc<T>::sort(sortFunc, arr, 0, n);
    for (int j = 1; j < n; ++j) {
        assert(arr[j - 1] <= arr[j]);
    }
    delete[] arr;
}

template <typename T, typename F>
void sortNormalRandom(F&& sortFunc, size_t n, T l = numeric_limits<T>::min(),
                      T r = numeric_limits<T>::max()) {
    sortFunc.reset();
    T* arr = new T[n];
    normal_distribution<double> u(l, r);
    for (int j = 0; j < n; ++j) {
        arr[j] = static_cast<T>(u(e));
    }
    SortFunc<T>::sort(sortFunc, arr, 0, n);
    for (int j = 1; j < n; ++j) {
        assert(arr[j - 1] <= arr[j]);
    }
    delete[] arr;
}

template <typename T, typename F>
void sortInc(F&& sortFunc, size_t n) {
    sortFunc.reset();
    T* arr = new T[n];
    for (int j = 0; j < n; ++j) {
        arr[j] = j;
    }
    SortFunc<T>::sort(sortFunc, arr, 0, n);
    for (int j = 1; j < n; ++j) {
        assert(arr[j - 1] <= arr[j]);
    }
    delete[] arr;
}

template <typename T, typename F>
void sortDec(F&& sortFunc, size_t n) {
    sortFunc.reset();
    T* arr = new T[n];
    for (int j = 0; j < n; ++j) {
        arr[j] = n - j;
    }
    SortFunc<T>::sort(sortFunc, arr, 0, n);
    for (int j = 1; j < n; ++j) {
        assert(arr[j - 1] <= arr[j]);
    }
    delete[] arr;
}

template <typename T, typename F>
void sortSame(F&& sortFunc, size_t n) {
    sortFunc.reset();
    T* arr = new T[n];
    memset(arr, 0, sizeof(T) * n);
    SortFunc<T>::sort(sortFunc, arr, 0, n);
    for (int j = 0; j < n; ++j) {
        assert(arr[j] == 0);
    }
    delete[] arr;
}

template <typename T>
class SortTest {
public:
    const static int seed = 1;
    SortTest(size_t n, T l = numeric_limits<T>::min(),
             T r = numeric_limits<T>::max())
        : n(n), l(l), r(r) {}

    template <typename F>
    void add() {
        sortFuncs.emplace_back(new F());
    }

    void test() {
        printf("\n==== sort uniform random\n");
        for (auto& sortFunc : sortFuncs) {
            e.seed(seed);
            sortUniformRandom<T>(*sortFunc, n, l, r);
        }
        printf("\n==== sort normal random\n");
        for (auto& sortFunc : sortFuncs) {
            e.seed(seed);
            sortNormalRandom<T>(*sortFunc, n, l, r);
        }
        printf("\n==== sort inc\n");
        for (auto& sortFunc : sortFuncs) {
            sortInc<T>(*sortFunc, n);
        }
        printf("\n==== sort dec\n");
        for (auto& sortFunc : sortFuncs) {
            sortDec<T>(*sortFunc, n);
        }
        printf("\n==== sort same\n");
        for (auto& sortFunc : sortFuncs) {
            sortSame<T>(*sortFunc, 10e3);
        }
    }

    vector<unique_ptr<SortFunc<T>>> sortFuncs;
    size_t n;
    T l;
    T r;
};

}  // namespace zfish

#endif  // SORT_TEST_H