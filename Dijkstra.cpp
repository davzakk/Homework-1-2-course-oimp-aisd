#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

#define int long long
using namespace std;

vector<vector<pair<int, int>>> g;
vector<int> d, p;
set<pair<int, int>> sett;
int n, k, s, f;

const int INF = 1e18;

main() {
    cin >> n >> s >> f;
    g.assign(n, {});
    p.assign(n, -1);
    d.assign(n, INF);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            cin >> w;
            if (w != -1) g[i].push_back({j, w});
        }
    }
    s--;
    f--;
    d[s] = 0;
    sett.insert({d[s], s});
    while (!sett.empty()) {
        int v = (*sett.begin()).second;
        sett.erase(sett.begin());
        for (auto u : g[v]) {
            int u_num = u.first, u_wei = u.second;
            if (d[v] + u_wei < d[u_num]) {
                sett.erase({d[u_num], u_num});
                d[u_num] = d[v] + u_wei;
                p[u_num] = v;
                sett.insert ({d[u_num], u_num});
            }
        }
    }
    if (d[f] == INF) cout << -1;
    else {
        cout << d[f];
    }
}
