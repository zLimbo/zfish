
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define psize(type)                                 \
    do {                                            \
        printf("%10s: %ld\n", #type, sizeof(type)); \
    } while (0);

class A {};

class B {
    virtual ~B() {}
};

class C {
    int x;
    short y;
    char z;
    int x2;
    char z2;
};

void f() {}

int main() {
    psize(char);
    psize(short);
    psize(int);
    psize(long);
    psize(long long);
    psize(long int);
    psize(long long int);
    psize(short int);
    psize(wchar_t);
    psize(A);
    psize(B);
    psize(C);
    C c;

    auto f2 = [c] {

    };
    psize(f2);

    return 0;
}