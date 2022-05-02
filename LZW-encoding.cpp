#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;

unordered_map<string, int> map_str_to_int;

signed main() {
    for (int i = 0; i < 128; ++i) {
        char c = (char) i;
        string ss;
        ss += c;
        map_str_to_int[ss] = i;
    }
    vector<int> ans;
    int counter = 128;
    string s, b;
    getline(cin, s);
    for (int i = 0; i < s.size(); ++i) {
        b += s[i];
        if (map_str_to_int.find(b) == map_str_to_int.end()) {
            map_str_to_int[b] = counter;
            counter++;
            ans.push_back(map_str_to_int[b.substr(0, b.size() - 1)]);
            b = b.substr(b.size() - 1, 1);
        }
    }
    ans.push_back(map_str_to_int[b]);
    cout << ans.size() << "\n";
    for (auto i : ans) cout << i << " ";
}
