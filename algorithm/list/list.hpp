#ifndef LIST_H
#define LIST_H

template <typename T>
class List {
public:
    struct Node {
        T x;
        Node *prev;
        Node *next;
        Node(const T &x, Node *prev = nullptr, Node *next = nullptr)
            : x(x), prev(prev), next(next) {}
    };

    List() : size_(0) {}

    void PushBack(const T &x) {
        
    }

private:
    int size_;
    Node *head_;
    Node *tail_;
};

#endif  // LIST_H