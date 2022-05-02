#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> prefix(string s) {
    vector<int> p(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        int k = p[i - 1];
        while (k > 0 && s[k] != s[i]) k = p[k - 1];
        if (s[k] == s[i]) ++k;
        p[i] = k;
    }
    return p;
}
int main() {
    string s;
    cin >> s;
    for (auto i : prefix(s)) cout << i << " ";
}
