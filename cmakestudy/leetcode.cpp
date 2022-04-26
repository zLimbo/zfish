#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int m = nums.size();
        int n = m / 2;

        for (int x : nums) cout << x << " ";
        cout << endl;

        vector<int> res(n);

        for (int i = n - 1; i < m - 1; ++i) {
            int d = nums[m - 1] - nums[i];
            if (d <= 0 || d % 2) continue;
            res[n - 1] = (nums[m - 1] + nums[i]) / 2;

            vector<int> isLow(m);
            isLow[i] = true;

            int h = m - 2;
            while (h >= 0 && isLow[h]) --h;

            bool ok = true;
            cout << "\n" << endl;
            cout << res[n - 1] << endl;
            for (int j = n - 2, up = i; j >= 0; --j) {
                auto it =
                    find(nums.begin() + j, nums.begin() + up, nums[h] - d);
                if (it == nums.begin() + up) {
                    ok = false;
                    break;
                }
                up = it - nums.begin();
                res[j] = (nums[h] + nums[up]) / 2;
                cout << j << " " << res[j] << " " << h << " " << up << endl;
                isLow[up] = true;

                --h;
                while (h >= 0 && isLow[h]) --h;
                up = min(up, h);
            }
            if (ok) return res;
        }
        cout << "error" << endl;
        return res;
    }
};

int main() {
    vector<int> arr = {11, 6, 3, 4, 8, 7, 8, 7, 9, 8, 9, 10, 10, 2, 1, 9};
    for (int x : Solution().recoverArray(arr)) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}