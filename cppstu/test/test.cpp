#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;

template <typename T, typename U>
auto add(T t, U u) {
    return t + u;
}

int main() {
    bool arr[] = {1, 0, 0, 1, 1};
    bool arr2[] = {0, 1, 0, 1, 1};
    vector<bool> v1(arr, arr + 5), v2(arr2, arr2 + 5);
    vector<bool> v3(v1.size());
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::logical_and<int>());
    copy(v3.rbegin(), v3.rend(), ostream_iterator<bool>(cout, " "));

    int a[10] = {0};
    auto b = a;

    auto f = [](auto x, auto y) { return x + y; };

    cout << typeid(f).name() << endl;

    return 0;
}