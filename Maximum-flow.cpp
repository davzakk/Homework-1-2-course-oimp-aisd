#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int n, m, ans = 0, a, b, w;
vector<vector<int>> c;

int main() {
    cin >> n >> m ;
    c.assign(n, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> w;
        c[a - 1][b - 1] = w;
    }
    while (1) {
        vector<int> parent(n, -1), used(n, 0);
        queue<int> q;
        used[0] = 1;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < n; i++) {
                if (!used[i] && c[v][i] > 0) {
                    parent[i] = v;
                    used[i] = 1;
                    q.push(i);
                }
            }
        }
        if (!used[n - 1]) break;
        int extra_flow = 1e9, cur_v = n - 1;
        while (cur_v) {
            extra_flow = min(extra_flow, c[parent[cur_v]][cur_v]);
            cur_v = parent[cur_v];
        }
        cur_v = n - 1;
        ans += extra_flow;
        while (cur_v) {
            c[cur_v][parent[cur_v]] += extra_flow;
            c[parent[cur_v]][cur_v] -= extra_flow;
            cur_v = parent[cur_v];
        }
    }
    cout << ans;
}
