
#include <iostream>
#include <vector>
using namespace std;

vector<int> cor;
vector<vector<int>> adj;
int res = 0;

int dfs(int u, int p, int pcor) {
    vector<int> chcor;
    int ucor = pcor | (1 << cor[u]);
    int all = 1 << cor[u];
    for (int v : adj[u]) {
        if (v == p)continue;
        int c = dfs(v, u, ucor);
        all |= c;
        chcor.push_back(c);
    }
    int n = chcor.size();
    for (int i = 0; i < n; ++i) {
        if (chcor[i] != 7)
            continue;
        int oth = ucor;
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                oth |= chcor[j];
                if (oth == 7) break;
            }
        }
        if (oth == 7) ++res;
    }
    // cout << u << " " << all << " " << pcor << endl;
    return all;
}

int main() {
    // freopen("in", "r", stdin);
    int n;
    cin >> n;
    cor.resize(n + 1);
    adj.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        if (c == 'r') cor[i] = 0;
        else if (c == 'g') cor[i] = 1;
        else cor[i] = 2;
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0, 0);
    cout << res << endl;
    return 0;
}