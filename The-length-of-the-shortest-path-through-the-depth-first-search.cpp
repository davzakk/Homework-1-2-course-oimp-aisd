#include <vector>
#include <iostream>
#include <queue>

using namespace std;

queue<int> q;
vector<int> d, p, used;
vector<vector<int>> g;

void bfs(int v) {
    q.push(v);
    used[v] = true;
    p[v] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (!used[u]) {
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    used.assign(n, 0);
    p.assign(n, 0);
    d.assign(n, 0);
    g.assign(n, {});
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            cin >> x;
            if (x) {
                g[i].push_back(j);
            }
        }
    }
    int startt, endd;
    cin >> startt >> endd;
    startt--;
    endd--;
    bfs(startt);
    if (startt == endd) {
        cout << 0;
        return 0;
    }
    if (d[endd] == 0) {
        cout << -1;
        return 0;
    }
    cout << d[endd];


}
