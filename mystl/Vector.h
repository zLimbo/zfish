#ifndef VECTOR
#define VECTOR

#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <ctime>
typedef int Rank;
#define DEFAULT_CAPACITY 4

void error() { throw std::runtime_error("error\n"); }

template <typename T>
class Vector {
protected:
    T *_elem;
    Rank _size;
    int _capacity;

    //不可访问接口
    void copyFrom(T const *A, Rank lo, Rank hi);
    bool expand();
    bool shrink();
    bool bubble(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);

public:
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size != s; ++_size) _elem[_size] = v;
    }
    Vector(T const &A, Rank n) { copyFrom(A, 0, n); }
    Vector(T const &A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
    //析构函数
    ~Vector() { delete[] _elem; }

    //只读访问接口
    Rank size() const { return _size; }
    Rank Size() const { return _size; }
    int capacity() const { return _capacity; }
    bool empty() const { return !_size; }
    int disordered() const;  //判断向量是否已排序
    Rank find(T const &e) const { return find(e, 0, _size); }
    Rank find(T const &e, Rank lo, Rank hi) const;  //无序查找
    Rank search(T const &e) const {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const &e, Rank lo, Rank hi) const;  //有序查找
#define LNode <T> *LNP(T)
    //可写访问接口
    T &operator[](Rank r) const;
    Vector<T> &operator=(Vector<T> const &v);
    T remove(Rank r);
    int remove(Rank lo, Rank hi);
    Rank insert(T const &e) { return insert(_size, e); }
    Rank insert(Rank r, T const &e);
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }
    void unsort(Rank lo, Rank hi);       //置乱
    void unsort() { unsort(0, _size); }  //置乱
    int deduplicate();                   //无序去重
    int uniquify();                      //有序去重

    //遍历
    void traverse(void (*)(T &));  //函数指针，只读或局部修改
    template <typename VST>
    void traverse(VST);  //函数对象，可全局修改

    void show() {
        std::cout << "elem: ";
        for (Rank i = 0; i != _size; ++i) std::cout << _elem[i] << " ";
        std::cout << std::endl;
        std::cout << "capacity: " << _capacity << "    size: " << _size
                  << std::endl;
    }
};  // Vector

template <typename T>
inline void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _capacity = DEFAULT_CAPACITY;
    while (_capacity < hi - lo) _capacity <<= 1;
    _elem = new T[_capacity];
    _size = 0;
    while (lo < hi) _elem[_size++] = A[lo++];
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &V) {
    if (_elem) delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
bool Vector<T>::expand() {
    if (_size < _capacity) return false;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (Rank i = 0; i < _size; ++i) _elem[i] = oldElem[i];
    delete[] oldElem;
    return true;
}

template <typename T>
bool Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY) return false;
    if (_size << 2 > _capacity) return false;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (Rank i = 0; i < _size; ++i) _elem[i] = oldElem[i];
    delete[] oldElem;
    return true;
}

template <typename T>
T &Vector<T>::operator[](Rank r) const {
    return _elem[r];
}

template <typename T>
void permute(Vector<T> &V) {
    for (int i = V.size(); i > 0; --i)
        std::swap(V[i - 1], V[rand() % i]);  // V[i-1]  v[0, i]
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T *V = _elem + lo;  //子向量 V[0, hi-lo]
    for (Rank i = hi - lo; i > 0; --i) std::swap(V[i - 1], V[rand() % i]);
}

template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]))
        ;
    return hi;
}
template <typename T>
Rank Vector<T>::insert(Rank r, T const &e) {
    expand();
    for (int i = _size; i > r; --i) _elem[i] = _elem[i - 1];
    _elem[r] = e;
    ++_size;
    return r;
}
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) return 0;
    while (hi < _size) _elem[lo++] = _elem[hi++];
    _size = lo;
    while (shrink())
        ;
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r) {
    if (_size <= 0) error();
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size) (find(_elem[i], 0, i) < 0) ? ++i : remove(i);
    return oldSize - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for (Rank i = 0; i < _size; ++i) visit(_elem[i]);
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST visit) {  //函数对象
    for (Rank i = 0; i < _size; ++i) visit(_elem[i]);
}

template <typename T>  //函数对象
struct Increase {
    virtual void operator()(T &e) { ++e; }
};

template <typename T>
void increase(Vector<T> &V) {
    V.traverse(Increase<T>());
}

template <typename T>
int Vector<T>::disordered() const {
    int cnt = 0;
    for (Rank i = 1; i < _size; ++i)
        if (_elem[i - 1] > _elem[i]) ++cnt;
    return cnt;
}

/*
template <typename T>      //low effective
int Vector<T>::uniquify() {
        int oldSize = _size;
        Rank i = 1;
        while (i < _size)
                (_elem[i-1] == _elem[i]) ?
                remove(i) : ++i;
        return oldSize - _size;
}

*/

template <typename T>  // high effective
int Vector<T>::uniquify() {
    Rank i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j]) _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}

template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const {
    // return (rand() % 2) ?
    //        binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
    return binSearch(_elem, e, lo, hi);
}
/*
template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) {
        while (lo < hi) {
                Rank mi = (lo + hi) >> 1;
                if (e < A[mi]) hi = mi;
                else if (A[mi] < e) lo = mi + 1;
                else return mi;
        }
        return -1;
}
*/
/*
template <typename T>
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi) {
        Fib fib(hi - lo);
        while (lo < hi) {
                while (hi - lo < fib.get()) fib.prev();
                Rank mi = lo + fib.get() - 1;
                if (e < A[mi] hi = mi;
                else if (A[mi] < e) lo = mi + 1;
                else return mi;
        }
        return -1;
}
*/
/*
template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) {
        while ( 1 < hi - lo) {
                Rank mi = (lo + mi) >> 1;
                (e < A[mi]) ? hi = mi : lo = mi;
        }
        return (e == A[lo]) ? lo : -1;
}
*/

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    /*
    switch(rand() % 5) {
            case 1: bubbleSort(lo, hi); break;
            case 2: selectionSort(lo, hi); break;
            case 3: mergeSort(lo, hi); break;
            case 4: heapSort(lo, hi); break;
            default: quickSort(lo,hi); break;
    }
    */
    switch (rand() % 2) {
        case 0:
            bubbleSort(lo, hi);
            break;
        case 1:
            mergeSort(lo, hi);
            break;
    }
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--))
        ;
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    while (++lo < hi)
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            std::swap(_elem[lo - 1], _elem[lo]);
        }
    return sorted;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) return;
    Rank mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T *A = _elem + lo;  // A[0, hi - lo)  = _elem[lo, hi)
    int lb = mi - lo;
    T *B = new T[lb];  // B[0, lb)  = _elem[lo, mi)
    for (Rank i = 0; i < lb; ++i) B[i] = A[i];
    int lc = hi - mi;
    T *C = _elem + mi;  // C[0, lc)  = _elem[mi, hi)
    Rank i = 0, j = 0, k = 0;
    while (j < lb && k < lc)
        if (B[j] < C[k])
            A[i++] = B[j++];
        else
            A[i++] = C[k++];
    while (j < lb) A[i++] = B[j++];
    while (k < lc) A[i++] = C[k++];
    delete[] B;
}

#endif
