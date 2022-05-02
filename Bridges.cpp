#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>

using namespace std;

void dfs_bridges(int v, int p, vector<int>& used, vector<int>& up, vector<int>& tin, int t, vector<vector<int>>& g, unordered_map<int, int>& mapp, unordered_map<int, int>& mat, vector<int>& vec, int& n){
    used[v] = 1;
    up[v] = tin[v] = t++;
    for (int u : g[v]){
        if (u == p) continue;
        if (used[u]){
            up[v] = min(up[v], tin[u]);
        }
        else{
            dfs_bridges(u, v, used, up, tin, t, g, mapp, mat, vec, n);
            up[v] = min(up[v], up[u]);
            if (up[u] > tin[v]){
                if (mat[min(u, v) * n + max(u, v)] == 1) vec.push_back(mapp[min(u, v) * n + max(u, v)]);
            }
        }
    }
}

vector<int> find_bridges(vector<vector<int>>& g, unordered_map<int, int>& mapp, unordered_map<int, int>& mat) {
    int n = g.size();
    vector<int> used;
    vector<int> vec;
    int t;
    vector<int> tin, up;
    used.assign(n, 0);
    tin.assign(n, 0);
    up.assign(n, 0);
    t = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs_bridges(i, -1, used, up, tin, t, g, mapp, mat, vec, n);
        }
    }
    sort(vec.begin(), vec.end());
    return vec;
}




int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g;
    g.assign(n, {});
    unordered_map<int, int> mapp, mat;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
        mapp[min(a - 1, b - 1) * n + max(a - 1, b - 1)] = i + 1;
        mat[min(a - 1, b - 1) * n + max(a - 1, b - 1)]++;
    }
    cout << find_bridges(g, mapp, mat).size() << "\n";
    for (auto i : find_bridges(g, mapp, mat)) cout << i << " ";
}
