#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int n, s, e;
vector<vector<int>> mat;
vector<int> curr;
void f(vector<int>& cur, int counter, vector<vector<int>>& matt) {
    if (counter == s) {
        cout << "YES";
        std::exit(0);
    }
    vector<vector<int>> mattt(cur.size(), vector<int>(cur.size(), 0));
    for (int i = 0; i < cur.size(); ++i) {
        for (int j = i + 1; j < cur.size(); ++j) {
            mattt[i][j] = matt[cur[i]][cur[j]];
        }
    }
    vector<int> degs(cur.size(), 0);
    for (int i = 0; i < cur.size(); ++i) {
        for (int j = i + 1; j < cur.size(); ++j) {
            if (!mattt[i][j]) {
                degs[i]++;
                degs[j]++;
            }
        }
    }
    for (int v = 0; v < cur.size(); ++v) {
        if (degs[v] + counter + 1 < s) continue;
        vector<int> cur_2;
        for (int u = v + 1; u < cur.size(); ++u) {
            if (!mattt[v][u]) cur_2.push_back(u);
            if (cur_2.size() + counter + 1 + (cur.size() - v - 1) < s) break;
        }
        if (cur_2.size() + counter + 1 >= s) f(cur_2, counter + 1, mattt);
    }
}

int main() {
    cin >> n >> s >> e;
    mat.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) curr.push_back(i);
    for (int i = 0; i < e; ++i) {
        int v, u;
        cin >> v >> u;
        mat[v - 1][u - 1] = 1;
        mat[u - 1][v - 1] = 1;
    }
    f(curr, 0, mat);
    cout << "NO";
}
