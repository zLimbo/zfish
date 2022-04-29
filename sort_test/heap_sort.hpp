#ifndef HEAP_SORT_H
#define HEAP_SORT_H

namespace zfish {
namespace heap_sort {

template <typename T>
class V1 : public SortFunc<T> {
public:
    V1(const string& msg = "heap_sort_v1") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        heap_make(arr + l, r - l);
        for (int R = r - 1; cmp(R > 0); --R) {
            this->swap(arr[l], arr[R]);
            heap_down(arr + l, R - l, 0);
        }
    }

    void heap_down(T* arr, size_t n, size_t i) {
        T x = arr[i];
        while (true) {
            int imax = i * 2 + 1;
            if (cmp(imax >= n)) {
                arr[i] = x;
                break;
            }
            if (int j = i * 2 + 2; cmp(j < n) && cmp(arr[j] > arr[imax])) {
                imax = j;
            }
            if (cmp(arr[imax] <= x)) {
                arr[i] = x;
                break;
            }
            arr[i] = arr[imax];
            i = imax;
        }
    }

    void head_up(T* arr, size_t i) {
        T x = arr[i];
        while (cmp(i > 0)) {
            int p = (i - 1) / 2;
            if (cmp(arr[p] >= x)) {
                break;
            }
            arr[i] = arr[p];
            i = p;
        }
        arr[i] = x;
    }

    void heap_make(T* arr, size_t n) {
        for (int i = n / 2; cmp(i >= 0); --i) {
            heap_down(arr, n, i);
        }
    }
};

}  // namespace heap_sort
}  // namespace zfish

#endif  // HEAP_SORT_H