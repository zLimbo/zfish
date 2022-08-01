#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
template <typename T>
class List {
public:
    struct Node {
        T val;
        Node *prev;
        Node *next;
        Node(const T &x, Node *prev = nullptr, Node *next = nullptr)
            : val(x), prev(prev), next(next) {}
    };

    List() : size_(0), head_(nullptr), tail_(nullptr) {}

    void PushBack(const T &x) {
        ++size_;
        if (head_ == nullptr) {
            head_ = new Node(x);
            tail_ = head_;
            return;
        }
        tail_->next = new Node(x, tail_);
        tail_ = tail_->next;
    }

    T PopFront() {
        if (head_ == nullptr) {
            throw std::runtime_error("list is empty!");
        }
        T x = std::move(head_->val);
        Node *dummy = head_;
        head_ = head_->next;
        if (tail_ == dummy) {
            tail_ = nullptr;
        }
        delete dummy;
        return x;
    }

    void Transfer() const {
        for (Node *it = head_; it != nullptr; it = it->next) {
            std::cout << it->val << " ";
        }
        std::cout << std::endl;
    }

private:
    int size_;
    Node *head_;
    Node *tail_;
};

#endif  // LIST_H