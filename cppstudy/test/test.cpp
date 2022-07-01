#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct TestObj {
    TestObj() {
        cout << "TestObj" << endl;
    }
    void show() {
        std::cout << "show " << std::endl;
    }
};

template <typename T>
void show(T& obj) {
    { std::decay_t<decltype(T().show())>* _ = nullptr; }
    obj.show();
}

// template <typename T>
// void show(T& obj, std::decay_t<decltype(obj++)>* = nullptr) {
//     obj++;
//     std::cout << obj << std::endl;
// }

int main() {
    TestObj obj;
    show(obj);

    int val = 0;
    // show(val);
    return 0;
}