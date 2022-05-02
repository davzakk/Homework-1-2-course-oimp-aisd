#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;

unordered_map<int, string> m;

signed main() {
    for (int i = 0; i < 128; ++i) {
        char c = (char) i;
        string ss;
        ss += c;
        m[i] = ss;
    }
    int n, x, p_x = 0;
    cin >> n >> x;
    string b;
    if (m.find(x) != m.end()) {
        b += m[x];
        p_x = x;
    }
    for (int i = 1; i < n; ++i) {
        cin >> x;
        if (m.find(x) == m.end()) {
            b += m[p_x] + m[p_x][0];
            m[m.size()] = m[p_x] + m[p_x][0];
        } else {
            b += m[x];
            m[m.size()] = m[p_x] + m[x][0];// + m[x + 1][0];
        }
        p_x = x;
    }
    cout << b;
}
