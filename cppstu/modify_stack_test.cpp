#include <stdio.h>

typedef struct {
    int a[2];
    double d;
} struct_t;

int rbp1, rbp2, addr1, addr2;
int N = 9;

double func(int i, int j, int x = 24, int y = 25, int z = 26) {
    volatile struct_t s;
    if (i == N) {
        rbp1 = s.a[8];
        rbp2 = s.a[9];
        addr1 = s.a[10];
        addr2 = s.a[11];
    }
    if (i == 0) {
        s.a[8] = rbp1;
        s.a[9] = rbp2;
        s.a[10] = addr1;
        s.a[11] = addr2;
        return 0.0;
    }
    printf("i = %d start\n", i);
    func(i - 1, i - 2);
    printf("i = %d end\n", i);
    return s.d;
}

int main() {
    func(N, N - 1);
    return 0;
}