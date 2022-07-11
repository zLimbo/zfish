#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Obj {
public:
    void *operator new(size_t n, int cnt) {
        printf("new, %d\n", cnt);
        return ::operator new(n);
    }
    Obj() { printf("default cons\n"); }
};

int main() {
    std::allocator<Obj> alloc;
    Obj *arr = alloc.allocate(10);

    for (int i = 0; i < 10; ++i) {
        alloc.construct(arr + i);
        alloc.destroy(arr + i);
    }

    alloc.deallocate(arr, 10);

    return 0;
}