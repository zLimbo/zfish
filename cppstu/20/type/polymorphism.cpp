#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace fmt;

struct Base {
    void print() const {
        ::print("Base\n");
    }
};

struct Derive : Base {
    void print() const {
        ::print("Derive\n");
    }
};

std::unique_ptr<Base> bp = make_unique<Base>(Derive{});

auto p = bp.get();

int main() {
    bp->print();
    p->print();

    return 0;
}