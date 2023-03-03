#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace fmt;

struct Base {};
struct Children {
    [[no_unique_address]] Base base;
    int other;
};
static_assert(sizeof(Children) == 4);


int main() {
    
    return 0;
}