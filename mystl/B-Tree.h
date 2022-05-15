#ifndef B - TREE_H_INCLUDED
#define B -TREE_H_INCLUDED

#include "Vector.h"

#define BTNodePosi(T) BTNode<T> *

template <typename T>
struct BTNode {
    BTNodePosi(T) parent;
    Vector<T> key;
    Vector<BTNodePosi(T)> child;
    BTNode() : parent(nullptr) { child.insert(0, nullptr); }
    BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr) {
        parent = nullptr;
        key.insert(0, e);
        child.insert(0, lc);
        if (lc) lc->parent = this;
        child.insert(1, rc);
        if (rc) rc->parent = this;
    }
};

template <typename T>
class BTree {
protected:
    int _size;
    int _order;
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;
    void solveOverflow(BTNodePosi(T));
    void solveUnderflow(BTNodePosi(T));

public:
    BTree(int order = 3) : _order(order), _size(0) { _root = new BTNode<T>(); }
    ~BTNode() {
        if (_root) release(_root);
    }
    int order const { return _order; }
    int size const { return _size; }
    BTNodePosi(T) & root() { return _root; }
    bool empty() const { return !_size; }
    BTNodePosi(T) search(const T &e);
    bool insert(const T &e);
    bool remove(const T &e);
};

template <typename T>
BTNodePosi(T) BTree<T>::search(const T &e) {
    BTNodePosi(T) v = _root;
    _hot = nullptr;
    while (v) {
        Rank r = v->key.search(e);
        if ((0 <= r) && (e == v->key[r])) return v;
        _hot = v;
        v = v->child[r + 1];
    }
    return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T &e) {
    BTNodePosi(T) v = search(e);
    if (v) return false;
    Rank r = _hot->key.search(e);
    _hot->key.insert(r + 1, e);
    _hot->child.insert(r + 2, nullptr);
    ++_size;
    solveOverflow(_hot);
    return true;
}

/*

#include "Vector.h"

#define BTNodePosi(T) BTNode<T>*

template <typename T>
struct BTNode {
        BTNodePosi(T) parent;
        Vector<T> key;
        Vector<BTNodePosi(T)> child;
        BTNode() { parent = nullptr; child.insert(0, nullptr); }
        BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr) {
                parent = nullptr;
                key.insert(0, e);
                child.insert(0, lc);
                child.insert(1, rc);
                if (lc) lc->parent = this;
                if (rc) rc->parent = this;
        }
};

template <typename T>
class BTree {
protected:
        int _size;
        int _order;
        BTNodePosi(T) _root;
        BTNodePosi(T) _hot;
        void solveOverflow(BTNodePosi(T));
        void solveUnderflow(BTNodePosi(T));
public:
        BTree (int order = 3): _order(order), _size(0) {
                _root = new BTNode<T>();
        }
        ~BTree() { if (_root) delete _root; }
        int order() const { return _order; }
        int size() const { return _size; }
        BTNodePosi(T)& root() { return _root; }
        bool empty() const { return !_root; }
        BTNodePosi(T) search(const T &e);
        bool insert(const T &e);
        bool remove(const T &e);
};

template <typename T>
BTNodePosi(T) BTree<T>::search(const T &e) {
        BTNodePosi(T) v = _root;
        _hot = nullptr;
        while (v) {
                Rank r = v->key.search(e);
                if ( (0 <= r) && (e == v->key[r]) ) return v;
                _hot = v;
                v = v->child[r + 1];
        }
        return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T &e) {
        BTNodePosi(T) v = search(e);
        if (v) return false;
        Rank r = _hot->key.search(e);
         _hot->key.insert(r + 1, e);
        _hot->child.insert(r + 2, nullptr);
        ++_size;
        solveOverflow(_hot);
        return true;
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v) {
        if (_order >= v->child.size()) return;
        Rank s = _order / 2;
        BTNodePosi(T) u = new BTNode<T>();
        for (Rank j = 0; j < _order - s - 1; ++j) {
                u->child.insert(j, v->child.remove(s + 1));
                u->key.insert(j, v->key.remove(s + 1));
        }
        u->child.insert(_order - s - 1, v->child.remove(s + 1));
        if (u->child[0])
                for (Rank j = 0; j < _order - s; ++j)
                        u->child[j]->parent = u;
        BTNodePosi(T) p = v->parent;
        if (!p) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; }
        Rank r = 1 + p->key.search(v->key[0]);
        p->key.insert(r, v->key.remove(s));
        p->child.insert(r + 1, u);
        u->parent = p;
        solveOverflow(p);
}

template <typename T>
bool BTree<T>::remove(const T &e) {
        BTNodePosi(T) v = search(e);
        if (!v) return false;
        Rank r = v->key.search(e);
        if (v->child[0]) {
                BTNodePosi(T) u = v->child[r + 1];
                while (u->child[0]) u = u->child[0];
                v->key[r] = u->key[0];
                v = u;
                r = 0;
        }
        v->key.remove(r);
        v->child.remove(r+1);
        --_size;
        solveUnderflow(v);
        return true;
}



template <typename T>
void BTree<T>::solveUnderflow(BtNodePosi(T) v) {
        if ( (_order + 1) / 2 <= v->child.size() ) return;
        BTNodePosi(T) p = v->parent;
        if (!p) {
                if (!v->key.size() && v->child[0]) {
                        _root = v->child[0];
                }


                */
#endif  // B-TREE_H_INCLUDED
