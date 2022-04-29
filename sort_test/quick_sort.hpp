#ifndef QUICK_SORT_H
#define QUICK_SORT_H

namespace zfish {
namespace quick_sort {

template <typename T>
class V11 : public SortFunc<T> {
public:
    V11(const string& msg = "quick_sort_v11") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        if (cmp(r <= l + 1)) return;
        uniform_int_distribution<size_t> u(l, r - 1);
        this->swap(arr[u(e)], arr[l]);
        T x = arr[l];
        int L = l + 1, R = r - 1;
        while (true) {
            while (cmp(L <= R) && cmp(arr[L] <= x)) ++L;
            while (cmp(L <= R) && cmp(arr[R] >= x)) --R;
            if (cmp(L >= R)) break;
            this->swap(arr[L++], arr[R--]);
        }
        this->swap(arr[l], arr[R]);
        this->operator()(arr, L, r);
        this->operator()(arr, l, R);
    }
};

template <typename T>
class V12 : public SortFunc<T> {
public:
    V12(const string& msg = "quick_sort_v12") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        if (cmp(r <= l + 1)) return;
        uniform_int_distribution<size_t> u(l, r - 1);
        this->swap(arr[u(e)], arr[l]);
        T x = arr[l];
        int L = l + 1, R = r - 1;
        while (true) {
            while (cmp(L <= R) && cmp(arr[L] <= x)) ++L;
            while (cmp(L <= R) && cmp(arr[R] >= x)) --R;
            if (cmp(L >= R)) break;
            this->swap(arr[L++], arr[R--]);
        }
        this->swap(arr[l], arr[R]);
        while (cmp(L < r) && cmp(arr[L] == x)) ++L;
        while (cmp(R > l + 1) && cmp(arr[R - 1] == x)) --R;
        this->operator()(arr, L, r);
        this->operator()(arr, l, R);
    }
};

template <typename T>
class V13 : public SortFunc<T> {
public:
    V13(const string& msg = "quick_sort_v13") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        if (cmp(r <= l + 1)) return;
        this->swap(arr[(l + r) / 2], arr[l]);
        T x = arr[l];
        int L = l + 1, R = r - 1;
        while (true) {
            while (cmp(L <= R) && cmp(arr[L] <= x)) ++L;
            while (cmp(L <= R) && cmp(arr[R] >= x)) --R;
            if (cmp(L >= R)) break;
            this->swap(arr[L++], arr[R--]);
        }
        this->swap(arr[l], arr[R]);
        this->operator()(arr, L, r);
        this->operator()(arr, l, R);
    }
};

template <typename T>
class V14 : public SortFunc<T> {
public:
    V14(const string& msg = "quick_sort_v14") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        while (true) {
            if (cmp(r <= l + 1)) return;
            this->swap(arr[(l + r) / 2], arr[l]);
            T x = arr[l];
            int L = l + 1, R = r - 1;
            while (true) {
                while (cmp(L <= R) && cmp(arr[L] <= x)) ++L;
                while (cmp(L <= R) && cmp(arr[R] >= x)) --R;
                if (cmp(L >= R)) break;
                this->swap(arr[L++], arr[R--]);
            }
            this->swap(arr[l], arr[R]);
            this->operator()(arr, L, r);
            r = R;
        }
    }
};

template <typename T>
class V15 : public SortFunc<T> {
public:
    V15(const string& msg = "quick_sort_v15") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        while (true) {
            if (cmp(r <= l + 1)) return;
            this->swap(arr[(l + r) / 2], arr[l]);
            T x = arr[l];
            int L = l + 1, R = r - 1;
            while (true) {
                while (cmp(L <= R) && cmp(arr[L] <= x)) ++L;
                while (cmp(L <= R) && cmp(arr[R] >= x)) --R;
                if (cmp(L >= R)) break;
                this->swap(arr[L++], arr[R--]);
            }
            this->swap(arr[l], arr[R]);
            while (cmp(L < r) && cmp(arr[L] == x)) ++L;
            while (cmp(R > l + 1) && cmp(arr[R - 1] == x)) --R;
            this->operator()(arr, L, r);
            r = R;
        }
    }
};

template <typename T>
class V21 : public SortFunc<T> {
public:
    V21(const string& msg = "quick_sort_v21") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        if (cmp(r <= l + 1)) return;
        uniform_int_distribution<size_t> u(l, r - 1);
        this->swap(arr[u(e)], arr[l]);
        int x = arr[l];
        int L = l;
        for (int R = l + 1; cmp(R < r); ++R) {
            if (cmp(arr[R] < x)) {
                this->swap(arr[++L], arr[R]);
            }
        }
        this->swap(arr[l], arr[L]);
        this->operator()(arr, l, L);
        this->operator()(arr, L + 1, r);
    }
};

template <typename T>
class V22 : public SortFunc<T> {
public:
    V22(const string& msg = "quick_sort_v22") : SortFunc<T>(msg) {}

    virtual void sort(T* arr, size_t l, size_t r) override {
        if (cmp(r <= l + 1)) return;
        uniform_int_distribution<size_t> u(l, r - 1);
        this->swap(arr[u(e)], arr[l]);
        int x = arr[l];
        int L = l;
        for (int R = l + 1; cmp(R < r); ++R) {
            if (cmp(arr[R] <= x)) {
                this->swap(arr[++L], arr[R]);
            }
        }
        this->swap(arr[l], arr[L]);
        this->operator()(arr, l, L);
        this->operator()(arr, L + 1, r);
    }
};

}  // namespace quick_sort
}  // namespace zfish

#endif  // QUICK_SORT_H