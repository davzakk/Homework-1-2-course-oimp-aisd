#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs2_topsort(int v, int prev, vector<vector<int>>& g, vector<int>& used, vector<int>& ans, vector<int>& used2, vector<int>& st, bool& f) {
    if (f) {
        return;
    }
    st.push_back(v);
    used2[v] = 1;
    for (auto i : g[v]) {
        if (f) {
            return;
        }
        if (used2[i] == 0) {
            dfs2_topsort(i, v, g, used, ans, used2, st, f);
        } else if (used2[i] == 1) {
            st.push_back(i);
            f = 1;
            return;
        }
    }
    st.pop_back();
    used2[v] = 2;
}

void dfs_topsort(int v, vector<vector<int>>& g, vector<int>& used, vector<int>& ans, vector<int>& used2, vector<int>& st, bool& f) {
    used[v] = 1;
    for (auto i : g[v]) {
        if (!used[i]) {
            dfs_topsort(i, g, used, ans, used2, st, f);
        }
    }
    ans.push_back(v);
}

vector<int> topsort(vector<vector<int>>& g) {
    vector<int> used;
    vector<int> ans, used2, st;
    bool f = false;
    int n = g.size();
    used2.resize(n, 0);
    used.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (!used2[i]) {
            dfs2_topsort(i, -1, g, used, ans, used2, st, f);
            if (f) {
                break;
            }
        }
    }
    if (f) {
        return {};
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs_topsort(i, g, used, ans, used2, st, f);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}




int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g;
    g.assign(n, {});
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x - 1].push_back(y - 1);
    }
    if (topsort(g).empty()) {
        cout << -1;
        return 0;
    }
    for (auto i : topsort(g)) {
        cout << i + 1 << " ";
    }
}
