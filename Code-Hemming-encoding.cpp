#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> pow2 = {1};

int f(int x) {
    int i = 0;
    while (pow2[i] <= x + i) i++;
    return i;
}

signed main() {
    for (int i = 0; i < 30; ++i) pow2.push_back(pow2.back() * 2);
    string s;
    cin >> s;
    vector<int> ans(f(static_cast<int>(s.size())) + s.size() + 1, 0);
    for (int i = 0, j = 1, z = 0; j < ans.size(); ++j) {
        if (pow2[i] == j) i++;
        else {
            ans[j] = s[z] - '0';
            z++;
        }
    }
    for (auto i : pow2) {
        int summ = 0;
        for (int j = i; j < ans.size(); j += 2 * i)
            for (int z = j; z < j + i; ++z)
                if (z < ans.size()) summ += ans[z];
        if (i < ans.size()) ans[i] = summ % 2;
    }
    for (int i = 1; i < ans.size(); ++i) cout << ans[i];
}
