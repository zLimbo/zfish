#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

using namespace std;

int main() {
    vector<int> v(5);
    iota(v.begin(), v.end(), 0);

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

    cout << endl;

    cout << is_sorted(v.begin(), v.end()) << endl;

    cout << endl;

    while (next_permutation(v.begin(), v.end())) {
        copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    return 0;
}