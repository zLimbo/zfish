#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "matrix.hpp"

using namespace std;

template <typename T>
class Obj {
    void f() { char c = "afj"; }
};

int main() {
    bustub::RowMatrix<int> x(2, 2), y(2, 2), z(2, 2);

    bustub::RowMatrixOperations<int>::GEMM(&x, &y, &z);
    bustub::RowMatrixOperations<int>::Add(&x, &y);
    bustub::RowMatrixOperations<int>::Multiply(&x, &y);

    Obj<int> o;

    // o.f();

    return 0;
}