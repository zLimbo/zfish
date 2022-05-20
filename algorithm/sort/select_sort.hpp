#ifndef SELECT_SORT_H
#define SELECT_SORT_H

namespace zfish {
namespace select_sort {

template <typename T>
class V1 : public SortFunc<T> {
public:
    V1(const string& msg = "select_sort_v1") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        for (int i = l; cmp(i < r); ++i) {
            int minIdx = i;
            for (int j = i + 1; cmp(j < r); ++j) {
                if (cmp(arr[j] < arr[minIdx])) {
                    minIdx = j;
                }
            }
            this->swap(arr[i], arr[minIdx]);
        }
    }
};

}  // namespace select_sort
}  // namespace zfish

#endif  // SELECT_SORT_H