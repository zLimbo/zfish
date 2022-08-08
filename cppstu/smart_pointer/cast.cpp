#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct A {};

struct B : A {};

int main() {
    auto pb = make_shared<B>();
    shared_ptr<A> pa = pb;
    shared_ptr<B> pb2 = dynamic_pointer_cast<B>(pa);

    return 0;
}