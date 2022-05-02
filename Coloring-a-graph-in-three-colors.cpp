#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> g;
vector<set<char>> cand;
string start_color;

void f(int cur_pos, vector<set<char>>& cands) {
    int cur_pos_copy = cur_pos;
    while (cur_pos_copy != n - 1 && cands[cur_pos_copy].size() == 1) cur_pos_copy++;
    if (cur_pos == n) {
        for (auto& i : cands) cout << *i.begin();
        std::exit(0);
    }
    for (char color_1 : cands[cur_pos_copy]) {
        vector<set<char>> cands_copy = cands;
        cands_copy[cur_pos_copy] = {color_1};
        queue<int> q;
        q.push(cur_pos_copy);
        int flag = 0;
        while (!q.empty()) {
            int v = q.front();
            char color = *cands_copy[v].begin();
            q.pop();
            for (auto i : g[v]) {
                if (cands_copy[i].find(color) != cands_copy[i].end()) {
                    cands_copy[i].erase(color);
                    if (cands_copy[i].empty()) {
                        flag = 1;
                        q = queue<int>();
                        break;
                    }
                    q.push(i);
                }
            }
        }
        if (!flag) f(cur_pos_copy + 1, cands_copy);
    }
}

int main() {
    cin >> n >> m >> start_color;
    for (auto i : start_color) {
        cand.push_back({});
        for (auto j : {'R', 'G', 'B'}) if (i != j) cand.back().insert(j);
    }
    g.assign(n, {});
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
        g[u - 1].push_back(v - 1);
    }
    f(0, cand);
    cout << "Impossible";
}
