#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A {};

struct B : A {
    int x, y;
};

int main() {
    cout << sizeof(A) << " " << sizeof(B) << endl;
    cout << &B::x << endl;
    cout << &B::y << endl;
    return 0;
}