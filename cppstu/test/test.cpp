#include <iostream>

#include <vector>
#include <functional>
using namespace std;

using LL = long long;

int main() {
    LL n, k;
    cin >> n >> k;
    vector<LL> a(n), b(n), c(n);
    for (LL i = 0; i < n; ++i) cin >> a[i];
    for (LL i = 0; i < n; ++i) cin >> b[i];
    for (LL i = 0; i < n; ++i) cin >> c[i];
    
    vector<vector<LL>> dp(n, vector<LL>(k + 1));
    vector<vector<LL>> vis(n, vector<LL>(k + 1));
    
    function<LL(LL,LL)> dfs = [&](LL i, LL j) -> LL {
        if (i >= n) return 0;
        if (vis[i][j]) {
            return dp[i][j];
        }
        
        LL x = dfs(i + 1, j) + a[i];
        if (j >= c[i]) {
            x = max(x, dfs(i + 1, j - c[i]) + b[i]);
        }
        dp[i][j] = x;
        vis[i][j] = 1;
        return x;
    };
    
    LL res = 1500 + dfs(0, k);
    cout << res << endl;
    
    return 0;
}