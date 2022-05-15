// cpp
// heap

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

template<typename T, typename Cmp=less<T>>
bool heap_check(vector<T>& v, int low, int high, Cmp cmp=Cmp()) {
    if (high - low < 2) return true;
    for (int i = 0; i < (high - low) / 2; ++i) {
        assert(!cmp(v[low + i], v[low + 2 * i + 1]));
        assert(!cmp(v[low + i], v[low + 2 * i + 2]));
    }
    if (high - low & 1) {
        assert(!cmp(v[low + (high - low - 1) / 2], v[high]));
    }
    return true;
}


template<typename T, typename Cmp=less<T>>
void heap_filter(vector<T>& v, int low, int high, int parent, Cmp cmp=Cmp()) {
    T x = move(v[low + parent]);
    while (parent < (high - low) / 2) {
        int child = parent * 2 + 1;
        if (cmp(v[low + child], v[low + child + 1])) ++child;
        if (cmp(x, v[low + child])) {
            v[low + parent] = move(v[low + child]);
            parent = child;
        } else break;
    }
    if (parent == (high - low - 1) / 2 && (high - low & 1)) {
        int child = parent * 2 + 1;
        if (cmp(x, v[low + child])) {
            v[low + parent] = move(v[low + child]);
            parent = child;
        }
    }
    v[low + parent] = move(x);
}


template<typename T, typename Cmp=less<T>>
void heap_make(vector<T>& v, int low, int high, Cmp cmp=Cmp()) {
    if (high - low < 2) return;
    int parent = (high - low - 1) / 2;
    while (parent >= 0) {
        heap_filter(v, low, high, parent, cmp);
        --parent;
    }
}


template<typename T, typename Cmp=less<T>>
void heap_push(vector<T>& v, int low, int high, Cmp cmp=Cmp()) {
    int child = high - low;
    T x = move(v[low + child]);
    while (child > 0) {
        int parent = (child - 1) / 2;
        if (cmp(v[low + parent], x)) {
            v[low + child] = move(v[low + parent]);
            child = parent;
        } else break;
    }
    v[low + child] = move(x);
}


template<typename T, typename Cmp=less<T>>
void heap_pop(vector<T>& v, int low, int high, Cmp cmp=Cmp()) {
    swap(v[low], v[high--]);
    heap_filter(v, low, high, 0, cmp);
}


template<typename T, typename Cmp=less<T>>
void heap_sort(vector<T>& v, int low, int high, Cmp cmp=Cmp()) {
    while (low < high) {
        swap(v[low], v[high--]);
        heap_filter(v, low, high, 0, cmp);
    }
}


int main() {

    vector<int> v;

    for (int i = 0; i < 100; ++i) {
        int val = rand() % 100;
        v.push_back(val);
    }

    heap_make(v, 0, v.size() - 1);
    heap_check(v, 0, v.size() - 1);

    for (int x: v) cout << x << " "; cout << endl;

    heap_sort(v, 0, v.size() - 1);
    for (int x: v) cout << x << " "; cout << endl;

    return 0;
}