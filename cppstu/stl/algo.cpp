#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<int> x = {1, 2, 3, 4, 3, 3, 4, 2, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 4, 2, 4};
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());

    copy_if(begin(x), end(x), ostream_iterator<int>(cout, " "), [](int e) { return e > 2; });
    cout << endl;
    next_permutation(x.begin(), x.end());
    for_each(x.begin(), x.end(), [](int e) { cout << e << " "; });
    cout << endl;

    return 0;
}