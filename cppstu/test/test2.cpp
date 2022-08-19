#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

struct Food {
    int cook = 0;
    int need = 0;
};

struct Block {
    int live = 3;
    int fire = 0;
    int out = 0;
    int haveout = 0;
    vector<Food> foods;
};

int main() {
    int w, h;
    cin >> w >> h;
    vector<vector<Block>> bs(w, vector<Block>(h));
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y, t;
        cin >> x >> y >> t;
        bs[x][y].foods.push_back(Food{0, t});
    }
    int m;
    cin >> m;
    map<int, vector<pair<int, int>>> fires;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        fires[c].emplace_back(a, b);
    }

    int t = fires.begin()->first;
    bool stop = false;
    while (!stop) {
        stop = true;
        vector<vector<Block>> bs2(w, vector<Block>(h));
        if (fires.count(t)) {
            auto &fv = fires[t];
            for (auto it: fv) {
                
            }
        }
    }

    return 0;
}