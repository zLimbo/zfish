#include <algorithm>
#include <iostream>
#include <set>
#include <shared_mutex>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string line;
    cin >> line;

    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == ',')
            line[i] = ' ';
    }
    // cout << line << endl;
    int k, x, y;
    istringstream sin(line);
    sin >> k >> x >> y;

    int t = k / 2;
    int gx = (x - 1) / t, gy = (y - 1) / t;

    if (gx == gy) {
        string res = "[A" + to_string(gx + 1) + "]";
        cout << res << endl;
        return 0;
    }

    string prefix = "[A" + to_string(gx + 1);
    string suffix = " A" + to_string(gy + 1) + "]";

    set<string> us;

    int g2x = (x - 1) / (t * t);
    int g2y = (y - 1) / (t * t);
    if (g2x == g2y) {
        string s = "[A" + to_string(gx + 1);
        for (int i = 1; i <= t; ++i) {
            int j = g2x * t + i;
            s += "B" + to_string(j) + " ";
            string s = prefix + " B" + to_string(j) + suffix;
            cout << s << endl;
            us.insert(s);
        }
        return 0;
    }

    for (int i = 1; i <= t; ++i) {
        for (int j = 1; j <= t; ++j) {
            string s = " B" + to_string(g2x * t + i) + " ";
            s += "C" + to_string((i - 1) * t + j) + " ";
            s += "B" + to_string(g2y * t + i);
            s = prefix + s + suffix;
            // cout << s << endl;
            us.insert(s);
        }
    }

    return 0;
}