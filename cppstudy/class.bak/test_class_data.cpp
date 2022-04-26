#include <cassert>
#include <iostream>

using namespace std;

template <typename class_type, typename data_type1, typename data_type2>
const char *access_order(data_type1 class_type::*mem1,
                         data_type2 class_type::*mem2) {
    assert(mem1 != mem2);

    printf("%p %p\n", mem1, mem2);

    return "";
}

class Point3d {
public:
    // virtual void vfunc();
    float x;
    float y;
    float z;
};

int main() {
    access_order(&Point3d::x, &Point3d::y);

    return 0;
}