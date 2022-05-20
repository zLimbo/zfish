
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <algorithm>
#include <random>
using namespace std;

void kth(vector<int>& nums, int l, int r, int k) {
    if (l + 1 >= r) return;
    swap(nums[l], nums[l + (r - l) / 2]);
    int x = nums[l];
    int L = l + 1, R = r - 1;
    while (true) {
        while (L <= R && nums[L] <= x) ++L;
        while (L <= R && nums[R] >= x) --R;
        if (L >= R) break;
        swap(nums[L++], nums[R--]);
    }
    swap(nums[l], nums[R]);
    if (R - l < k) {
        kth(nums, L, r, k - (L - l));
    } else if (R - l > k) {
        kth(nums, l, R, k);
    }
}

int main() {
    vector<int> v(100);
    iota(v.begin(), v.end(), 0);
    default_random_engine e;
    shuffle(v.begin(), v.end(), e);

    for (int x : v) cout << x << " ";
    cout << endl;
    int k = 5;
    kth(v, 0, v.size(), k);
    int x = v[k];
    nth_element(v.begin(), v.begin() + k, v.end());
    int y = v[k];
    cout << "\nx = " << x << " y = " << y << endl;
    return 0;
}