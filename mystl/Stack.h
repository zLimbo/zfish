#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Vector.h"
template <typename T>
class Stack : protected Vector<T> {
public:
    using Vector<T>::empty;
    using Vector<T>::show;
    using Vector<T>::size;
    using Vector<T>::capacity;
    using Vector<T>::find;

    void push(const T& e) { Vector<T>::insert(size(), e); }
    T pop() { return Vector<T>::remove(size() - 1); }
    T& top() { return (*this)[size() - 1]; }

    //  bool empty() { return !Vector<T>::size(); }
};

#endif  // STACK_H_INCLUDED
/*
there are no arguments to ‘size’ that depend on a template parameter,
so a declaration of ‘size’ must be available [-fpermissive]|
*/
