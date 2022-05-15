#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

#pragma pack(1)

class A {};

class B {
    virtual void f() {}
};

class C {
    int a;
    char b;
};

class D {
    long long a;
    int b;
    char c;
    char d;
    int e;
};

int main() {
    A a;
    B b;
    C c;
    D d;

    printf("a.size=%ld b.size=%ld c.size=%ld d.size=%ld\n", sizeof(a),
           sizeof(b), sizeof(c), sizeof(d));

    return 0;
}

void *memmove(void *dest, const void *src, size_t len)

{
    char *d = (char *)dest;

    const char *s = (const char *)(src);

    if (d < s)

        while (len--) *d++ = *s++;

    else {
        const char *lasts = s + (len - 1);

        char *lastd = d + (len - 1);

        while (len--) *lastd-- = *lasts--;
    }

    return dest;
}