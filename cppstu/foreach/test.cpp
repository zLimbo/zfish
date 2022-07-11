#include <initializer_list>
#include <iostream>
#include <memory>

template <typename T>
class Container {
public:
    using iterator = T*;

    Container(std::initializer_list<T> lst) {
        size_ = lst.size();
        data_ = new T[size_];
        int idx = 0;
        for (auto& x : lst) {
            data_[idx++] = std::move(x);
        }
    }

    iterator begin() {
        return data_;
    }

    iterator end() {
        return data_ + size_;
    }

private:
    size_t size_;
    T* data_;
};

int main() {
    Container<int> c = {1, 2, 3, 4, 5, 6, 7};
    for (auto x : c) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}