#define _GLIBCXX_DEBUG
#include <vector>
#include <iostream>
#include <set>
#include <iomanip>
#include <queue>
#include <algorithm>

//#define double long double
using namespace std;

vector<int> p_v, sz_tree;

int find_main_v(int v) {
    if (p_v[v] != v) {
        p_v[v] = find_main_v(p_v[v]);
    }
    return p_v[v];
}

void merge(int v, int u) {
    v = find_main_v(v), u = find_main_v(u);
    if (sz_tree[v] > sz_tree[u])
        swap(v, u);
    p_v[v] = u;
    sz_tree[u] += sz_tree[v];
}


int main() {
    int n, m, ans = 0;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> edges(m, {-1, {-1, -1}});
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
        edges[i].second.first--;
        edges[i].second.second--;
    }
    p_v.assign(n, 0);
    sz_tree.assign(n, 1);
    for (int i = 0; i < n; i++) p_v[i] = i;
    sort(edges.begin(), edges.end());
    for (auto e : edges) {
        int v = e.second.first, u = e.second.second;
        if (find_main_v(v) != find_main_v(u)) {
            ans += e.first;
            merge(v, u);
        }
    }
    cout << ans;
}
