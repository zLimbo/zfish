#ifndef INSERT_SORT_H
#define INSERT_SORT_H

namespace zfish {
namespace insert_sort {

template <typename T>
class V1 : public SortFunc<T> {
public:
    V1(const string& msg = "insert_sort_v1") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        for (size_t i = l + 1; cmp(i < r); ++i) {
            for (size_t j = i; cmp(j > l); --j) {
                if (cmp(arr[j - 1] <= arr[j])) {
                    break;
                }
                this->swap(arr[j - 1], arr[j]);
            }
        }
    }
};

template <typename T>
class V2 : public SortFunc<T> {
public:
    V2(const string& msg = "insert_sort_v2") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        for (size_t i = l + 1; cmp(i < r); ++i) {
            T x = arr[i];
            for (size_t j = i; cmp(j > l); --j) {
                if (cmp(arr[j - 1] <= x)) {
                    arr[j] = x;
                    break;
                }
                arr[j] = arr[j - 1];
            }
        }
    }
};

}  // namespace insert_sort
}  // namespace zfish

#endif  // INSERT_SORT_H