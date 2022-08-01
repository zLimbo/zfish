#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int *p = 0;

    printf("addr: %p\n", p);
    int x = *p;
    printf("val: %d\n", x);

    return 0;
}