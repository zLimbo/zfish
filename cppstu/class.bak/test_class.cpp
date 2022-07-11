#include <cstring>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

template <typename T, int dim>
class Point {
public:
    Point(T corrds[dim]) {
        for (int i = 0; i < dim; ++i) _corrds[i] = corrds[i];
    }

    T& operator[](int index) {
        std::cout << 1 << std::endl;
        return _corrds[index];
    }

    T operator[](int index) const {
        std::cout << 2 << std::endl;
        return _corrds[index];
    }

private:
    T _corrds[dim];
};

void print(int arr[3]) {
    for (int i = 0; i < 3; ++i) std::cout << arr[i] << std::endl;
}

int main() {
    int corrds[3] = {1, 2, 3};

    Point<int, 3> point(corrds);
    int x = point[0];
    const int y = point[0];
    auto z = point[0];
    print(corrds);
    auto pa = std::shared_ptr<int>(new int(3));

    string s = 3;

    return 0;
}