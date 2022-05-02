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
                d[i][j] = max(d[i][j], min(d[i][k], d[k][j]));
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
        }
    }
    for (auto i : floyd(mat)) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << "\n";
    }
    return 0;
}
