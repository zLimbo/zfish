#ifndef SHELL_SORT_H
#define SHELL_SORT_H

namespace zfish {
namespace shell_sort {

template <typename T>
class V1 : public SortFunc<T> {
public:
    V1(const string& msg = "shell_sort_v1") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        for (int len = (r - l) / 2; cmp(len > 0); len /= 2) {
            for (int k = 0; cmp(k < len); ++k) {
                for (int i = l + len + k; cmp(i < r); i += len) {
                    T x = arr[i];
                    for (int j = i; cmp(j >= l + len); j -= len) {
                        if (cmp(arr[j - len] <= x)) {
                            arr[j] = x;
                            break;
                        }
                        arr[j] = arr[j - len];
                    }
                }
            }
        }
    }
};

template <typename T>
class V2 : public SortFunc<T> {
public:
    V2(const string& msg = "shell_sort_v2") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        for (int len = (r - l) / 2; cmp(len > 0); len /= 2) {
            for (int i = l + len; cmp(i < r); ++i) {
                T x = arr[i];
                for (int j = i - len; cmp(j >= 0); j -= len) {
                    if (cmp(arr[j] <= x)) {
                        arr[j + len] = x;
                        break;
                    }
                    arr[j + len] = arr[j];
                }
            }
        }
    }
};

}  // namespace shell_sort
}  // namespace zfish

#endif  // SHELL_SORT_H