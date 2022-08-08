
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    int res = 0;
    vector<int> v;
    function<void(int, int)> dfs = [&](int cur, int sum) {
        if (sum == 60) {
            int y = 1;
            for (int x = v.size(); x > 1; --x) {
                y *= x;
            }
            for (int x = n - v.size(); x > 1; --x) {
                y *= x;
            }
            res += y;
            return;
        }
        if (sum > 60 || cur == nums.size()) {
            return;
        }
        v.push_back(cur);
        sum += nums[cur];
        dfs(cur + 1, sum);
        v.pop_back();
        sum -= nums[cur];
        dfs(cur + 1, sum);
    };
    dfs(0, 0);
    cout << res << endl;
    return 0;
}