#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    copy_if(v.begin(), v.end(), ostream_iterator<int>(cout, ", "),
            bind(greater<int>{}, placeholders::_1, 4));

    return 0;
}