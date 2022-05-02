#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
vector<vector<int>> g;
vector<bool> used;

void dfs(int v) {
    used[v] = 1;
    for (auto i : g[v]) {
        if (!used[i]) {
            dfs(i);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    used.resize(n, 0);
    g.resize(n, {});
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);
    }
    dfs(0);
    int ans = 0;
    for (auto i : used) {
        ans += i;
    }
    cout << ans << "\n";
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            cout << i + 1 << " ";
        }
    }
}
