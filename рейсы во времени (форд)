#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

using namespace std;

const int INF = 1e18;

main() {
    int n, a, b, k;
    cin >> n >> a >> b >> k;
    vector<int> d(n, INF);
    a--;
    b--;
    d[a] = 0;
    vector<vector<int>> edges;
    for (int i = 0; i < k; ++i) {
        int q, w, e, r;
        cin >> q >> w >> e >> r;
        edges.push_back({q - 1, e - 1, w, r});
    }
    for (int i = 0; i < k + 1; ++i) {
        for (auto e : edges) {
            //cout << d[e[0]] << " " << e[2] << "\n";
            if (d[e[0]] < INF && d[e[0]] <= e[2]) {
                //cout << i;
                d[e[1]] = min(d[e[1]], e[3]);
            }
        }
    }
    cout << d[b];
}
