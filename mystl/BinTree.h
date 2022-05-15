#ifndef BINTREE_H_INCLUDED
#define BINTREE_H_INCLUDED

#include <algorithm>
#include <stdio.h>
#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

#define BinNodePosi(T) BinNode<T> *
#define stature(p) ((p) ? (p)->height : -1)
typedef enum { RB_RED, RB_BLACK } RBColor;

#define IsRoot(x) (!((x).parent))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x)                                        \
    (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc \
                              : (x)->parent->parent->lc)

#define FromParentTo(x) \
    (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

template <typename T>
struct BinNode {
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    int height;
    int npl;
    RBColor color;

    BinNode()
        : parent(nullptr), lc(nullptr), rc(nullptr), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr,
            BinNodePosi(T) rc = nullptr, int h = 0, int l = 1,
            RBColor c = RB_RED)
        : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    int size();
    int floor();
    BinNodePosi(T) insertAsLC(const T &);
    BinNodePosi(T) insertAsRC(const T &);
    BinNodePosi(T) succ();
    template <typename VST>
    void travLevel(VST &);
    template <typename VST>
    void travPre(VST &);
    template <typename VST>
    void travIn(VST &);
    template <typename VST>
    void traPost(VST &);

    bool operator<(const BinNode &bn) { return data < bn.data; }
    bool operator=(const BinNode &bn) { return data == bn.data; }
    bool operator>(const BinNode &bn) { return data > bn.data; }
    bool operator<=(const BinNode &bn) { return data <= bn.data; }
    bool operator>=(const BinNode &bn) { return data >= bn.data; }
    bool operator!=(const BinNode &bn) { return data != bn.data; }
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(const T &e) {
    return lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(const T &e) {
    return rc = new BinNode(e, this);
}

template <typename T>
int BinNode<T>::size() {
    if (IsLeaf(*this)) return 1;
    int tmpSize = 0;
    if (HasRChild(*this)) tmpSize += rc->size();
    if (HasLChild(*this)) tmpSize += lc->size();
    return tmpSize + 1;
}

template <typename T>
int BinNode<T>::floor() {
    int floor = 0;
    BinNodePosi(T) x = this;
    while (x && x->parent) {
        ++floor;
        x = x->parent;
    }
    return floor;
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) succ = this;
    if (HasRChild(*this)) {
        succ = rc;
        while (HasLChild(*succ)) succ = succ->lc;
    } else {
        while (IsRChild(*succ)) succ = succ->parent;
        succ = succ->parent;
    }
    return succ;
}

template <typename T>
class BinTree {
protected:
    int _size;
    BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T) x);
    void updateHeightAbove(BinNodePosi(T) x);

public:
    BinTree() : _size(0), _root(nullptr) {}
    ~BinTree() {
        if (0 < _size) remove(_root);
    }
    int size() const { return _size; }
    bool empty() const { return !_size; }
    BinNodePosi(T) root() const { return _root; }
    BinNodePosi(T) insertAsRoot(const T &e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T), const T &e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T), const T &e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T), BinTree<T> *&);
    BinNodePosi(T) attachAsRC(BinNodePosi(T), BinTree<T> *&);
    int remove(BinNodePosi(T) x);
    BinTree<T> *secede(BinNodePosi(T) x);
    template <typename VST>
    void travLevel(VST &visit) {
        if (_root) _root->travLevel(visit);
    }
    template <typename VST>
    void travPre(VST &visit) {
        if (_root) _root->travPre(visit);
    }
    template <typename VST>
    void travIn(VST &visit) {
        if (_root) _root->travIn(visit);
    }
    template <typename VST>
    void travPost(VST &visit) {
        if (_root) _root->travPost(visit);
    }

    bool operator==(const BinTree<T> &t) {
        return _root && t._root(_root == t._root);
    }
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
    return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, const T &e) {
    ++_size;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, const T &e) {
    ++_size;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> *&S) {
    if (x->lc = S->_root) x->lc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = nullptr;
    S->_size = 0;

    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&S) {
    if (x->rc = S->_root) x->rc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = nullptr;
    S->_size = 0;
    return x;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template <typename T>
static int removeAt(BinNodePosi(T) x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->rc) + removeAt(x->lc);
    delete x;
    return n;
}

template <typename T>
BinTree<T> *BinTree<T>::secede(BinNodePosi(T) x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    BinTree<T> *S = new BinTree<T>;
    S->_root = x;
    x->parent = nullptr;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}

template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST &visit) {
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST &visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST &visit) {
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template <typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S;
    BinNodePosi(T) tmp;
    S.push(x);
    while (!S.empty()) {
        tmp = S.pop();
        visit(tmp->data);
        if (HasRChild(*tmp)) S.push(tmp->rc);
        if (HasLChild(*tmp)) S.push(tmp->lc);
    }
};

template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST &visit,
                                 Stack<BinNodePosi(T)> &S) {
    while (x) {
        visit(x->data);
        S.push(x->rc);
        x = x->lc;
    }
}

template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        visitAlongLeftBranch(x, visit, S);
        if (S.empty()) break;
        x = S.pop();
    }
}

template <typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)> &S) {
    while (x) {
        S.push(x);
        x = x->lc;
    }
}

template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        goAlongLeftBranch(x, S);
        if (S.empty()) break;
        visit(x = S.pop());
        if (HasRChild(*x)) x = x->rc;
    }
}

template <typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        if (x) {
            S.push(x);
            x = x->lc;
        } else if (!S.empty()) {
            x = S.pop();
            visit(x->data);
            x = x->rc;
        } else
            break;
    }
}

template <typename T>
static void gotoHLVF(Stack<BinNodePosi(T)> &S) {
    while (BinNodePosi(T) x = S.top()) {
        if (HasLChild(*x)) {
            if (HasRChild(*x)) S.push(x->rc);
            S.push(x->lc);
        } else
            S.push(x->rc);
    }
    S.pop();
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST visit) {
    Stack<BinNodePosi(T)> S;
    if (x) S.push(x);
    while (!S.empty()) {
        if (S.top() != x->parent) gotoHLVF(S);
        x = S.pop();
        visit(x->data);
    }
}

template <typename T, typename VST>
void travPost_II(BinNodePosi(T) x, VST visit) {
    if (!x) return;
    Stack<BinNodePosi(T)> S;
    S.push(x);
    while (!S.empty()) {
        x = S.top();
        while (HasLChild(*x) || HasRChild(*x)) {
            if (HasLChild(*x)) {
                if (HasRChild(*x)) S.push(x->rc);
                S.push(x = x->lc);
            } else
                S.push(x = x->rc);
        }
        while (!S.empty()) {
            x = S.pop();
            visit(x->data);
            if (S.top() != x->parent) break;
        }
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST &visit) {
    Queue<BinNodePosi(T)> Q;
    BinNodePosi(T) x = this;
    if (x) Q.enqueue(x);
    while (!Q.empty()) {
        x = Q.dequeue();
        visit(x->data);
        if (HasLChild(*x)) Q.enqueue(x->lc);
        if (HasRChild(*x)) Q.enqueue(x->rc);
    }
}

template <typename T>
void showTree(BinNodePosi(T) x) {
    Queue<BinNodePosi(T)> Q;
    if (x) Q.enqueue(x);
    int floor = x->floor();
    int oldFloor = floor - 1;
    int cnt = 0;
    while (!Q.empty()) {
        x = Q.dequeue();
        floor = x->floor();
        if (floor > oldFloor) {
            cout << "  *** " << cnt << " ***";
            cnt = 0;
            printf("\n%3d  :  ", floor);
            //   cout << "\n" << floor << "  :  ";
            oldFloor = floor;
        }
        if (++cnt % 7 == 0) cout << "\n        ";
        cout << "(";
        if (x->lc)
            printf("%4d", x->lc->data);
        else
            printf("    ");
        cout << ",";
        printf("%4d", x->data);
        cout << ",";
        if (x->rc)
            printf("%4d", x->rc->data);
        else
            printf("    ");
        cout << ")  ";
        if (HasChild(*x)) {
            if (HasLChild(*x) && x->lc->data > x->data)
                cout << "\nerror\n" << endl;
            if (HasRChild(*x) && x->rc->data < x->data)
                cout << "\nerror\n" << endl;
        }
        if (HasLChild(*x)) Q.enqueue(x->lc);
        if (HasRChild(*x)) Q.enqueue(x->rc);
    }
    cout << "  *** " << cnt << " ***" << endl;
}

template <typename T>
void buildTree(const Vector<T> &TV, BinTree<T> &TTree) {
    Queue<BinNodePosi(T)> TQ;
    TQ.enqueue(TTree.insertAsRoot(TV[0]));
    size_t cnt = 1;
    while (cnt != TV.size()) {
        BinNodePosi(T) tmpBp = TQ.front();
        if (!HasLChild(*tmpBp)) {
            TQ.enqueue(TTree.insertAsLC(tmpBp, TV[cnt++]));
            cout << tmpBp->lc->data << endl;
        } else if (!HasRChild(*tmpBp)) {
            TQ.enqueue(TTree.insertAsRC(tmpBp, TV[cnt++]));
            cout << tmpBp->rc->data << endl;
        } else
            TQ.dequeue();
    }
    while (!TQ.empty()) TQ.dequeue();
}

#endif  // BINTREE_H_INCLUDED
