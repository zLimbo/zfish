#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

namespace zfish {
namespace bubble_sort {

template <typename T>
class V1 : public SortFunc<T> {
public:
    V1(const string& msg = "bubble_sort_v1") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        for (size_t R = r; cmp(R > l); --R) {
            bool ok = true;
            for (size_t i = l + 1; cmp(i < R); ++i) {
                if (cmp(arr[i - 1] > arr[i])) {
                    this->swap(arr[i - 1], arr[i]);
                    ok = false;
                }
            }
            if (ok) {
                break;
            }
        }
    }
};

}  // namespace bubble_sort
}  // namespace zfish

#endif  // BUBBLE_SORT_H