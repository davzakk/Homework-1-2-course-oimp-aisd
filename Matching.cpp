#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, ans = 0, v;
vector<vector<int>> g;
vector<int> par, used;

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i] - n;
        if (par[to] == -1 || dfs(par[to])) {
            par[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    g.assign(n + m, vector<int>());
    for (int i = 0; i < n; ++i) {
        while (cin >> v) {
            if (v == 0) break;
            g[i].push_back(n + v - 1);
            g[n + v - 1].push_back(i);
        }
    }
    par.assign(m, -1);
    for (int i = 0; i < n; ++i) {
        used.assign(n, false);
        dfs(i);
    }
    for (auto i : par) ans += (int) (i != -1);
    cout << ans << "\n";
    for (int i = 0; i < m; ++i) {
        if (par[i] != -1) {
            cout << par[i] + 1 << " " << i + 1 << "\n";
        }
    }
}
