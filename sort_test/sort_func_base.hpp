#ifndef SORT_FUNC_BASE_H
#define SORT_FUNC_BASE_H

#include <string>
#include <chrono>

namespace zfish {

namespace chrono = std::chrono;
using Second = chrono::duration<double>;

template <typename T>
class SortFunc {
public:
    SortFunc(const std::string& msg) : msg(msg) {}

    void operator()(T* arr, size_t l, size_t r) {
        ++call_count;
        ++call_depth;
        max_call_depth = std::max(max_call_depth, call_depth);
        sort(arr, l, r);
        --call_depth;
    }

    virtual void sort(T* arr, size_t l, size_t r) = 0;

    void swap(T& lhs, T& rhs) {
        ++swap_count;
        std::swap(lhs, rhs);
    }

    void print(size_t n) {
        printf(
            "> [%14s] (size:%ld) (take:%8fs) (cmp:%8ld) (swap:%8ld) "
            "(call:%7ld) "
            "(maxDepth:%5ld)\n",
            msg.c_str(), n, take, cmp_count, swap_count, call_count,
            max_call_depth);
    }

    static void sort(SortFunc& sortFunc, T* arr, size_t l, size_t r) {
        auto before = chrono::steady_clock::now();
        sortFunc(arr, l, r);
        sortFunc.take +=
            chrono::duration_cast<Second>(chrono::steady_clock::now() - before)
                .count();
        sortFunc.print(r - l);
    }

    void reset() {
        take = 0.0;
        cmp_count = 0;
        swap_count = 0;
        call_count = 0;
        call_depth = 0;
        max_call_depth = 0;
    }

    std::string msg;
    double take{0.0};
    size_t cmp_count{0};
    size_t swap_count{0};
    size_t call_count{0};
    size_t call_depth{0};
    size_t max_call_depth{0};
};

#define cmp(exp) (++this->cmp_count, exp)

}  // namespace zfish

#endif  // SORT_FUNC_BASE_H