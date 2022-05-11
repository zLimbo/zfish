#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

int main() {
    
    string s;
    s.push_back(255);

    for (int i = 0; i < s.size(); ++i) {
        int x = (unsigned char)s[i];
        cout << x << endl;
    }

    return 0;
}