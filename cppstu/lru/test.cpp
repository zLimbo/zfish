#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <iterator>

// #include "lru_replacer.h"
using namespace std;

int main() {
    // bustub::LRUReplacer lru(10);

    // for (int i = 0; i < 10; ++i) {
    //     lru.Unpin(i);
    // }

    // lru.Pin(5);
    // lru.Pin(6);

    // for (int i = 0; i < 10; ++i) {
    //     int id;
    //     bool ok = lru.Victim(&id);
    //     cout << ok << " " << id << endl;
    // }

    list<int> lst{1};

    auto it = --lst.end();
    lst.insert(lst.begin(), {2, 3, 4});
    lst.insert(lst.end(), {2, 3, 4});

    copy(lst.begin(), lst.end(), ostream_iterator<int>{cout, " "});
    cout << endl;

    cout << *it << endl;

    lst.erase(it);
    copy(lst.begin(), lst.end(), ostream_iterator<int>{cout, " "});
    cout << endl;

    int arr[10];

    cout << (&arr[9] - arr) << endl;

    return 0;
}