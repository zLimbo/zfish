#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#include <cstdlib>
#include <algorithm>
#include <ctime>

typedef int Rank;
#define ListNodePosi(T) ListNode<T> *

template <typename T>
struct ListNode;
template <typename T>
class List;

template <typename T>
struct ListNode {
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;

    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
        : data(e), pred(p), succ(s) {}

    ListNodePosi(T) insertAsPred(const T &e);
    ListNodePosi(T) insertAsSucc(const T &e);
};  // ListNode

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T &e) {
    ListNodePosi(T) newNode = new ListNode<T>(e, pred, this);
    pred->succ = newNode;
    pred = newNode;
    return newNode;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T &e) {
    ListNodePosi(T) newNode = new ListNode<T>(e, this, succ);
    succ->pred = newNode;
    succ = newNode;
    return newNode;
}

template <typename T>
class List {
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;

protected:
    void init();
    void copyNodes(ListNodePosi(T), int);
    void merge(ListNodePosi(T) &, int, List<T> &, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T) &, int);
    void selectionSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);
    ListNodePosi(T) posiRank(Rank r) const;

public:
    List() { init(); }
    List(const List<T> &L);
    List(const List<T> &L, Rank r, int n);
    List(ListNodePosi(T) p, int n);

    ~List();

    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    int clear();
    T &operator[](Rank r) const;
    ListNodePosi(T) begin() const { return header->succ; }
    ListNodePosi(T) end() const { return trailer; }
    ListNodePosi(T) rbegin() const { return trailer->pred; }
    ListNodePosi(T) rend() const { return header; }
    bool valid(ListNodePosi(T) p) {
        return p && (trailer != p) && (header != p);
    }
    int disordered() const;
    ListNodePosi(T) find(const T &e) const { return find(e, _size, trailer); }
    ListNodePosi(T) find(const T &e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) search(const T &e, int n, ListNodePosi(T)) const;
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax() { return selectMax(begin(), _size); }

    ListNodePosi(T) insertAsLast(const T &e);
    ListNodePosi(T) insertAsFirst(const T &e);
    ListNodePosi(T) insertAsSucc(ListNodePosi(T) p, const T &e);
    ListNodePosi(T) insertAsPred(ListNodePosi(T) p, const T &e);
    T remove(ListNodePosi(T) p);
    void merge(List<T> &L) { merge(begin(), _size, L, L.begin(), L._size); }
    void sort(ListNodePosi(T) p, int n, int k = 0);
    void sort() { sort(begin(), _size); }
    int deduplicate();
    int uniquify();
    void reverse();

    // traverse
    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);
    void show() {
        std::cout << "size: " << _size << std::endl;
        std::cout << "elements: ";
        ListNodePosi(T) p = begin();
        while (p != trailer) {
            std::cout << p->data << " ";
            p = p->succ;
        }
        std::cout << std::endl;
    }
};  // List

template <typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pred = nullptr;
    header->succ = trailer;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template <typename T>
T &List<T>::operator[](Rank r) const {
    ListNodePosi(T) p = begin();
    while (0 < r--) p = p->succ;
    return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(const T &e, int n, ListNodePosi(T) p) const {
    while (0 < n--) {
        p = p->pred;
        if (e == p->data) return p;
    }
    return nullptr;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(const T &e) {
    ++_size;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(const T &e) {
    ++_size;
    return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsSucc(ListNodePosi(T) p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsPred(ListNodePosi(T) p, const T &e) {
    ++_size;
    return p->insertAsPred(e);
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();
    while (n--) {
        insertAsFirst(p->data);
        p = p->succ;
    }
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n) {
    copyNodes(p, n);
}

template <typename T>
List<T>::List(const List<T> &L) {
    copyNodes(L.begin(), L._size);
}

template <typename T>
ListNodePosi(T) List<T>::posiRank(Rank r) const {
    ListNodePosi(T) p = begin();
    while (0 < r--) p = p->succ;
    return p;
}

template <typename T>
List<T>::List(const List<T> &L, Rank r, int n) {
    copyNodes(L.posiRank(r), n);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    --_size;
    return e;
}

template <typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (0 < _size) remove(begin());
    return oldSize;
}

template <typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

template <typename T>
int List<T>::deduplicate() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = begin()->succ;
    Rank r = 1;
    while (p != end()) {
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : ++r;
        p = p->succ;
    }
    return oldSize - _size;
}

template <typename T>
void List<T>::traverse(void (*visit)(T &)) {
    for (ListNodePosi(T) p = begin(); p != end(); p = p->succ) visit(p->data);
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit) {
    for (ListNodePosi(T) p = begin(); p != end(); p = p->succ) visit(p->data);
}

template <typename T>
int List<T>::uniquify() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = begin();
    ListNodePosi(T) q;
    while ((q = p->succ) != end())
        if (p->data == q->data)
            remove(q);
        else
            p = q;
    return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(const T &e, int n, ListNodePosi(T) p) const {
    while (0 < n--)
        if (((p = p->pred)->data) <= e) break;
    return p;
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n, int k) {
    switch (k) {
        case 0:
            mergeSort(p, n);
            break;
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectionSort(p, n);
            break;
    }
}

template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n) {
    for (Rank r = 0; r < n; ++r) {
        insertAsSucc(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (Rank r = 0; r < n; ++r) tail = tail->succ;
    while (1 < n) {
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertAsPred(tail, remove(max));
        tail = tail->pred;
        --n;
    }
}

template <typename T>
bool lt(T a, T b) {
    return a < b;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
    ListNodePosi(T) max = p;
    for (ListNodePosi(T) cur = p; 1 < n; --n)
        if (!lt((cur = cur->succ)->data, max->data)) max = cur;
    return max;
}

template <typename T>
void List<T>::merge(ListNodePosi(T) & p, int n, List<T> &L, ListNodePosi(T) q,
                    int m) {
    ListNodePosi(T) pp = p->pred;
    while (0 < m) {
        if (0 < n && (p->data < q->data)) {
            if (q == (p = p->succ)) break;
            --n;
        } else {
            insertAsPred(p, L.remove((q = q->succ)->pred));
            --m;
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T) & p, int n) {
    if (n < 2) return;
    int m = n >> 1;
    ListNodePosi(T) q = p;
    for (Rank i = 0; i < m; ++i) q = q->succ;
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
}

#endif  // LIST_INCLUDED
