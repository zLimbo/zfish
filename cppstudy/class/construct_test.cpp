#include <iostream>

using namespace std;

class A {
public:
    virtual void f() {}
    A() {
        cout << "A" << endl;
        cout << ((int *)this - 1) << endl;
    }
};

class B : public A {
public:
    virtual void f() override{};
    B() {
        cout << "B" << endl;
        cout << ((int *)this - 1) << endl;
    }
};

class C {
public:
    C() { cout << "C" << endl; }
};

class D {
public:
    D(int val) : c() {}
    A a;
    B b;
    C c;
};

class E {
public:
    int a;
    char *b;
};

int main() {
    E e1;
    e1.a = 2;
    e1.b = "12345";

    E e2 = e1;
    cout << e2.a << " " << e2.b << endl;

    return 0;
}