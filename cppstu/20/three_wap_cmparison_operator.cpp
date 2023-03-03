#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

struct Four {
    int v1, v2, v3, v4;
    friend auto operator<=>(const Four& lhs, const Four& rhs) = default;
};

static_assert(Four{1,2,3,4} < Four{1,2,3,5});

int main() {
    
    return 0;
}