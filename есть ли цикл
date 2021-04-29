#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> floyd(vector<vector<int>> mat) {
    vector<vector<int>> d = mat;
    int n = d.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    return d;


}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> mat[i][j];
            mat[i][j] *= -1;
            if (mat[i][j] == 0 && i != j) mat[i][j] = 1e9;
        }
    }
    int ans = 0;
    vector<vector<int>> d = floyd(mat);
    for (int i = 0; i < n; ++i) {
        ans = min(ans, d[i][i]);
    }
    if (ans == 0) cout << 0;
    else cout << 1;
}
