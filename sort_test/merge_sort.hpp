#ifndef MERGE_SORT_H
#define MERGE_SORT_H

namespace zfish {
namespace merge_sort {

template <typename T>
class V1 : public SortFunc<T> {
public:
    V1(const string& msg = "merge_sort_v1") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        if (cmp(l + 1 >= r)) {
            return;
        }
        int mid = l + (r - l) / 2;
        this->operator()(arr, l, mid);
        this->operator()(arr, mid, r);
        T* larr = new T[mid - l];
        for (int i = l; cmp(i < mid); ++i) {
            larr[i - l] = arr[i];
        }
        int i = 0, j = mid, k = l;
        while (cmp(i + l < mid) && cmp(j < r)) {
            if (cmp(larr[i] < arr[j])) {
                arr[k++] = larr[i++];
            } else {
                arr[k++] = arr[j++];
            }
        }
        while (cmp(i + l < mid)) {
            arr[k++] = larr[i++];
        }
        delete[] larr;
    }
};

}  // namespace merge_sort
}  // namespace zfish

#endif  // MERGE_SORT_H