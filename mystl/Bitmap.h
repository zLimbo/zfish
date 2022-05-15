#ifndef Bitmap_H_INCLUDED
#define Bitmap_H_INCLUDED

#include <cstdio>
#include <cstring>

class Bitmap1 {
private:
    char *_Bitmap1;
    int _size;

    void init(int n) {
        _Bitmap1 = new char[_size = (n + 7) / 8];
        memset(_Bitmap1, 0, _size);
    }

    void expand(int k) {
        if (k < _size * 8) return;
        int OldSize = _size;
        char *Oldmap = _Bitmap1;
        init(k * 2);
        memcpy(_Bitmap1, Oldmap, OldSize);
        delete[] Oldmap;
    }

public:
    Bitmap1(int n = 8) { init(n); }
    Bitmap1(char *file, int n = 8) {
        init(n);
        FILE *fp = fopen(file, "r");
        fread(_Bitmap1, sizeof(char), _size, fp);
        fclose(fp);
    }
    ~Bitmap1() { delete[] _Bitmap1; }

    int size() { return _size; }

    void set(int k) {
        expand(k);
        _Bitmap1[k >> 3] |= (0x80 >> (k & 0x07));
    }
    void clear(int k) {
        expand(k);
        _Bitmap1[k >> 3] &= ~(0x80 >> (k & 0x07));
    }
    bool test(int k) {
        expand(k);
        return _Bitmap1[k >> 3] & (0x80 >> (k & 0x07));
    }

    void dump(char *file) {
        FILE *fp = fopen(file, "w");
        fwrite(_Bitmap1, sizeof(char), _size, fp);
        fclose(fp);
    }

    char *bits2string(int n) {
        expand(n - 1);
        char *str = new char[n + 1];
        for (int i = 0; i < n; ++i) str[i] = test(i) ? '1' : '0';
        str[n] = '\0';
        return str;
    }
};

typedef int Rank;

class Bitmap2 {
private:
    Rank *_data;
    Rank _size;
    Rank *_stack;
    Rank _top;

protected:
    bool vaild(Rank r) { return (0 <= r) && (r < _top); }
    bool erased(Rank r) {
        return vaild(_data[r]) && !(_stack[_data[r]] + r + 1);
    }
    void init(Rank n) {
        _size = n;
        _data = new Rank[_size];
        _stack = new Rank[_size];
        _top = 0;
    }
    inline void expand(Rank r) {
        if (r < _size) return;
        Rank *oldStack = _stack;
        Rank oldTop = _top;
        init(r * 2);
        for (int i = 0; i < oldTop; ++i) set(oldStack[i]);
        delete[] oldStack;
    }

public:
    Bitmap2(Rank n = 8) { init(n); }
    ~Bitmap2() {
        delete[] _data;
        delete[] _stack;
    }

    inline int size() { return _size; }
    inline void set(Rank r) {
        expand(r);
        if (test(r)) return;
        if (!erased(r)) _data[r] = _top++;
        _stack[_data[r]] = r;
    }

    inline void clear(Rank r) {
        if (test(r)) _stack[_data[r]] = -1 - r;
    }

    inline bool test(Rank r) {
        expand(r);
        return vaild(_data[r]) && _stack[_data[r]] == r;
    }
    void show() {
        for (int i = 0; i < _size; ++i) std::cout << (test(i) ? 1 : 0);
    }
};

void Eratosthenes(int n, char *file) {
    Bitmap1 a(n);
    a.set(0);
    a.set(1);
    for (int i = 2; i * i <= n; ++i)
        if (!a.test(i)) {
            for (int j = i * i; j < n; j += i) a.set(j);
        }
    a.dump(file);

    // for (int i = 0; i < n; ++i)
    //         if (!a.test(i)) std::cout << i << " ";

    // std::cout << endl;
}

#endif  // Bitmap_H_INCLUDED
