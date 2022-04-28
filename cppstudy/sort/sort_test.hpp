#ifndef SORT_TEST_H
#define SORT_TEST_H

#include <functional>
#include <random>
#include <chrono>
#include <cassert>
#include <string>
#include <limits>
#include <memory>

namespace zfish {

using namespace std;
using Second = chrono::duration<double>;

static default_random_engine e;

template <typename T>
class SortFunc {
public:
    SortFunc(const string& msg) : msg(msg) {}

    virtual void operator()(T* arr, size_t l, size_t r) = 0;

    void swap(T& lhs, T& rhs) {
        ++swap_count;
        std::swap(lhs, rhs);
    }

    double take{0.0};
    string msg;
    size_t cmp_count{0};
    size_t swap_count{0};
};

#define cmp(exp) (++this->cmp_count, exp)

namespace quick_sort {

template <typename T>
class V1 : public SortFunc<T> {
public:
    V1(const string& msg = "quick_sort_v1") : SortFunc<T>(msg) {}

    virtual void operator()(T* arr, size_t l, size_t r) override {
        if (r - l <= 1) return;
        uniform_int_distribution<size_t> u(l, r - 1);
        this->swap(arr[u(e)], arr[l]);
        T x = arr[l];
        int L = l + 1, R = r - 1;
        while (true) {
            while (L <= R && cmp(arr[L] <= x)) ++L;
            while (L <= R && cmp(arr[R] >= x)) --R;
            if (L >= R) break;
            this->swap(arr[L++], arr[R--]);
        }
        this->swap(arr[l], arr[R]);
        while (L < r && cmp(arr[L] == x)) ++L;
        while (R - 1 > l && cmp(arr[R - 1] == x)) --R;
        operator()(arr, L, r);
        operator()(arr, l, R);
    }
};

template <typename T>
class V2 : public SortFunc<T> {
public:
    V2(const string& msg = "quick_sort_v2") : SortFunc<T>(msg) {}

    virtual void operator()(T* arr, size_t l, size_t r) override {
        if (r - l <= 1) return;
        uniform_int_distribution<size_t> u(l, r - 1);
        this->swap(arr[u(e)], arr[l]);
        T x = arr[l];
        int L = l + 1, R = r - 1;
        while (true) {
            while (L <= R && cmp(arr[L] <= x)) ++L;
            while (L <= R && cmp(arr[R] >= x)) --R;
            if (L >= R) break;
            this->swap(arr[L++], arr[R--]);
        }
        this->swap(arr[l], arr[R]);
        operator()(arr, L, r);
        operator()(arr, l, R);
    }
};

}  // namespace quick_sort

template <typename T>
void print(T* arr, int l, int r) {
    for (int i = l; i < r; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T, typename F>
void sortFuncTest(F&& sortFunc, size_t n, size_t m,
                  T l = numeric_limits<T>::min(),
                  T r = numeric_limits<T>::max()) {
    T* arr = new T[n];
    uniform_int_distribution<T> u(l, r);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[j] = u(e);
        }
        // print(arr, 0, n);
        auto before = chrono::steady_clock::now();
        sortFunc(arr, 0, n);
        sortFunc.take +=
            chrono::duration_cast<Second>(chrono::steady_clock::now() - before)
                .count();
        // print(arr, 0, n);
    }
    for (int i = 1; i < n; ++i) {
        assert(arr[i - 1] <= arr[i]);
    }
    printf("> [%s] (size:%ld) (times:%ld) (take:%fs) (cmp:%ld) (swap:%ld)\n",
           sortFunc.msg.c_str(), n, m, sortFunc.take, sortFunc.cmp_count,
           sortFunc.swap_count);
    delete[] arr;
}

template <typename T>
class SortTest {
public:
    SortTest(size_t n, size_t m, T l = numeric_limits<T>::min(),
             T r = numeric_limits<T>::max())
        : n(n), m(m), l(l), r(r) {}

    template <typename F>
    void add() {
        sortFuncs.emplace_back(new F());
    }

    void test() {
        for (auto& sortFunc : sortFuncs) {
            e.seed(0);
            sortFuncTest<T>(*sortFunc, n, m, l, r);
        }
    }

    vector<unique_ptr<SortFunc<T>>> sortFuncs;
    size_t n;
    size_t m;
    T l;
    T r;
};

}  // namespace zfish

#endif  // SORT_TEST_H