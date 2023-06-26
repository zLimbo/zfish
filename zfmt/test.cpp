#include <string>
#include <vector>

#include "debug.h"

using namespace std;

int main() {
    vector<int> v{0, 1, 2, 3};
    zl::print(v);
    zl::print(zl::RED, v);
    vector<string> vs{"hello", "world", "!"};
    zl::print(zl::GREEN, string("green: "), vs);

    zl::print(string("hello world!"));
    zl::print(zl::BLUE, string("hello world!"));

    return 0;
}
