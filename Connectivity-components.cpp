#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
vector<vector<int>> g;
vector<bool> used;
pair<int, vector<int>> x = {0, {}};


void dfs(int v) {
    x.first++;
    x.second.push_back(v);
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
    vector<pair<int, vector<int>>> vec;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            x = {0, {}};
            dfs(i);
            vec.push_back(x);
        }
    }
    cout << vec.size() << "\n";
    //sort(vec.begin(), vec.end(), [](pair<int, vector<int>> x, pair<int, vector<int>> y){return x.second[0] < y.second[0];});
    for (auto i : vec) {
        cout << i.first << "\n";
        for (auto j : i.second) {
            cout << j + 1 << " ";
        }
        cout << "\n";
    }

}
