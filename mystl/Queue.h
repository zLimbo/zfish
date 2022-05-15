#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "List.h"

template <typename T>
class Queue : protected List<T> {
public:
    using List<T>::size;
    using List<T>::show;
    using List<T>::empty;

    void enqueue(const T& e) { List<T>::insertAsLast(e); }
    T dequeue() { return List<T>::remove(List<T>::begin()); }
    T& front() { return List<T>::begin()->data; }
};

#endif  // QUEUE_H_INCLUDED
