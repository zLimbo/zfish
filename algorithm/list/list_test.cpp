#include "list.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    List<int> lst;

    for (int i = 0; i < 10; ++i) {
        lst.PushBack(i);
    }

    lst.Transfer();

    for (int i = 0; i < 10; ++i) {
        cout << lst.PopFront() << " ";
    }
    cout << endl;

    cout << "<<< " << endl;

    lst.Transfer();

    cout << ">>> " << endl;
    for (int i = 0; i < 10; ++i) {
        lst.PushBack(i);
    }

    lst.Transfer();

    for (int i = 0; i < 10; ++i) {
        cout << lst.PopFront() << " ";
    }
    cout << endl;

    cout << "<<< " << endl;

    lst.Transfer();

    cout << ">>> " << endl;
    for (int i = 0; i < 10; ++i) {
        lst.PushBack(i);
    }

    lst.Transfer();

    return 0;
}