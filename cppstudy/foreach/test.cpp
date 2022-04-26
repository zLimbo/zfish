#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Obj {
public:
    int* begin() { return arr; }

    int* end() { return arr + 10; }

    int arr[10];

    Obj() {
        for (int i = 0; i < 10; ++i) {
            arr[i] = i;
        }
    }
};
int main() {
    Obj obj;
    for (auto p : obj) {
        cout << p << endl;
    }
    return 0;
}