#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <variant>

using namespace std;

int main() {
    
    variant<double, bool, string> var;

    struct {
        void operator()(int) { cout << "int!\n"; }
        void operator()(string const&) { cout << "string!\n"; }
    } visitor;

    
    var = 22.0;
    visit(visitor, var);
    var = "22";
    visit(visitor, var);

    return 0;
}