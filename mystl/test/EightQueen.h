#ifndef EightQueen
#define EightQueen

#include "../Stack.h"

struct Queen;
void show(Stack<Queen> &, int);
void placeQueens(int);

struct Queen {
    int x, y;
    Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {}
    Queen(const Queen &q) {
        x = q.x;
        y = q.y;
    }
    Queen &operator=(const Queen &q) {
        x = q.x;
        y = q.y;
        return *this;
    }
    bool operator==(const Queen &q) const {
        return (x == q.x) || (y == q.y) || (x - q.x == y - q.y) ||
               (x - q.x == q.y - y);
    }
    bool operator!=(const Queen &q) const { return !(*this == q); }
};

void show(Stack<Queen> &solu, int N) {
    int a[N][N];
    for (int i = 0; i != N; ++i)
        for (int j = 0; j != N; ++j) a[i][j] = 0;
    while (!solu.empty()) {
        Queen t = solu.pop();
        a[t.x][t.y] = 1;
        std::cout << "(" << t.x << "," << t.y << ")"
                  << " ";
    }
    std::cout << std::endl;
    ;
    for (int i = N - 1; i >= 0; --i) {
        for (int j = N - 1; j >= 0; --j) std::cout << a[i][j] << " ";
        std::cout << std::endl;
        ;
    }
}

void placeQueens(int N) {
    Stack<Queen> solu;
    Queen q(0, 0);
    int num = 0;
    while (true) {
        if (q.y == N || q.x == N) {
            q = solu.pop();
            q.y++;
            if (solu.empty() && q.y == N) break;
        } else {
            while (q.y < N && solu.find(q) >= 0) ++q.y;
            if (q.y < N) {
                solu.push(q);
                ++q.x;
                q.y = 0;
            }
        }
        if (solu.size() == N) {
            Stack<Queen> t;
            t = solu;
            show(t, N);
            ++num;
        }
    }
    if (num == 0)
        std::cout << "There is no solution." << std::endl;
    else
        std::cout << "\nThere " << (num == 1 ? "is " : "are ") << num
                  << " solution" << (num == 1 ? "." : "s.") << std::endl;
}

#endif
