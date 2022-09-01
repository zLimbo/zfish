#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct A {
    A() {
        cout << "A" << endl;
    }
    ~A() {
        cout << "~A" << endl;
    }
};

struct B {
    B() {
        cout << "B" << endl;
    }
    ~B() {
        cout << "~B" << endl;
    }
};

struct C {
    C() {
        cout << "C" << endl;
    }
    virtual ~C() {
        cout << "~C" << endl;
    }
    virtual void f() {
        cout << "C::f" << endl;
    }
    A a;
    B b;
};

struct D : public C {
    D() {
        cout << "D" << endl;
    }
    void f() {
        cout << "D::f" << endl;
    }
    ~D() {
        cout << "~D" << endl;
    }
};

struct E : public D {
    E() {
        cout << "E" << endl;
    }
    void f() {
        cout << "E::f" << endl;
    }
    ~E() {
        cout << "~E" << endl;
    }
};

void f(C& c) {
    c.f();
}

int main() {
    D d;
    f(d);
    E e;
    f(e);

    

    return 0;
}