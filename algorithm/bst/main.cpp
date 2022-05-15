#include <iostream>
#include <stdlib.h>
#include <assert.h>

#include "mytest.h"
#include "BinarySearchTree.hpp"

using namespace std;
using namespace zLimbo;

int main() {
    BinarySearchTree<int> bst;

    for (int i = 0; i < 10; ++i) {
        int e = rand() % 100;
        cout << e << "\t";
        cout << (bst.insert(e) ? "insert true" : "insert false") << "\t";
        cout << (bst.search(e) ? "search true" : "search false") << endl;
    }
    cout << endl;

    auto inorder = [&]() {
        int p = INT_MIN;
        int cnt = 0;
        for (int e : bst.inorder()) {
            cout << e << " ";
            assert(p < e);
            p = e;
            ++cnt;
        }
        cout << endl;
        cout << "tree size: " << bst.size() << endl;
        cout << "vec size: " << cnt << endl;
    };

    bst.showTree();

    inorder();
    int e = 67;
    cout << "remove:" << e << " is " << bst.remove(e) << endl;

    inorder();

    return 0;
}
