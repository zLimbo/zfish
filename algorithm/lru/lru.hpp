#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <list>
#include <stdexcept>
#include <unordered_map>

template <typename T>
class LRUList {
public:
    LRUList(int size) : size_(size) {}

    void push(T x) {
        auto it = map_.find(x);
        if (it != map_.end()) {
            lst_.erase(it->second);
        }
        if (lst_.size() >= size_) {
            throw std::runtime_error("overflow");
        }
        lst_.push_back(x);
        map_[x] = --lst_.end();
    }

    T pop() {
        if (lst_.empty()) {
            throw std::runtime_error("lst empty");
        }
        T x = std::move(lst_.front());
        lst_.pop_front();
        map_.erase(x);
        return x;
    }

    void show() const {
        for (T x : lst_) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

private:
    int size_;
    std::list<T> lst_;
    std::unordered_map<T, typename std::list<T>::iterator> map_;
};

#endif  // LRU_H