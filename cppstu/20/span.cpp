#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <span>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace fmt;

void passArrayLike(span<int> container) {
    println("container.size(): {}", container.size());
    for (auto elem : container) {
        print("{} ", elem);
    }
    println("\n");
}

int main() {
    int arr[]{1, 2, 3, 4};
    vector vec{1, 2, 3, 4, 5};
    array arr2{1, 2, 3, 4, 5, 6};

    passArrayLike(arr);
    passArrayLike(vec);
    passArrayLike(arr2);

    return 0;
}