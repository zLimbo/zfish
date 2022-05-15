#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "BST.h"

#define Balanced(x) ( stature( (x).lc ) ) == ( stature( (x).rc ) )
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc) )
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) )
#define tallerChild(x) ( \
        stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( \
        stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( \
        IsLChild( *(x) ) ? (x)->lc : (x)-> rc ) \
        ) \
)

template <typename T>
class AVL: public BST<T> {
private:
        using BST<T>::_hot;
        using BST<T>::_size;
        using BST<T>::_root;
public:
        using BST<T>::search;
        using BST<T>::size;
        using BST<T>::empty;
        using BST<T>::rotateAt;
        using BST<T>::updateHeight;
        BinNodePosi(T) insert(const T &e);
        bool remove(const T &e);
};

template <typename T>
BinNodePosi(T) AVL<T>::insert(const T &e) {
        BinNodePosi(T) &x = search(e);
        if (x) return x;
        BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);
        ++_size;
        for (BinNodePosi(T) g = _hot; g; g = g->parent) {
                if (!AvlBalanced(*g)) {
                        BinNodePosi(T) &gp = FromParentTo(*g);
                        gp = rotateAt(tallerChild(tallerChild(g)));
                        break;
                }
                else
                        updateHeight(g);
        }
        return xx;
}

template <typename T>
bool AVL<T>::remove(const T &e) {
        BinNodePosi(T) &x = search(e);
        if (!x) return false;
        removeAt(x, _hot);
        --_size;
        for (BinNodePosi(T) g = _hot; g; g = g->parent) {
                if (!AvlBalanced(*g)) {
                        BinNodePosi(T) &gp = FromParentTo(*g);
                        g = gp = rotateAt(tallerChild(tallerChild(g)));
                }
                updateHeight(g);
        }
        return true;
}



#endif // AVL_H_INCLUDED
