
#include <cstdint>

int64_t f(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8,
          int p9) {
    int x = 0;
    int y = 0;
    int64_t z = 0;
    int64_t l = 0;

    x++;
    p1++;
    p7++;
    p8++;
    p1 = p9 + p8;

    return 0;
}

int main() {
    int64_t i = 0;
    i++;
    i = f(1, 2, 3, 4, 5, 6, 7, 8, i);

    return 0;
}