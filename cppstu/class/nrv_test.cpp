#include <memory.h>

#include <iostream>

class Obj {
public:
    Obj() {
        memset(data, 0, 100 * sizeof(double));
        std::cout << "constructor" << std::endl;
    }
    Obj(const Obj &rhs) {
        std::cout << "copy" << std::endl;
    }
    Obj(const Obj &&rhs) {
        std::cout << "move" << std::endl;
    }

    double data[100];
};

Obj func() {
    Obj *obj = new Obj();
    obj->data[0] = 99;
    obj->data[99] = 99;
    return std::move(*obj);
}

void f(const Obj &v);

int main() {
    for (int i = 0; i < 1; ++i) {
        Obj obj = func();
    }

    f(Obj());

    return 0;
}