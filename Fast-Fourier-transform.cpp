#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <complex>

using namespace std;

const double PI = 3.14159265358979323846;

void bpf(vector<complex<long double>> &a, int n) {
    vector<int> rev(1 << n);
    for (int i = 1; i < (1 << n); i++) rev[i] = ((i & 1) << (n - 1)) | (rev[i >> 1] >> 1); //???
    for (int i = 0; i < (1 << n); i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int step = 0; step < n; step++) {
        complex<long double> w(cos(PI / (1 << step)), sin(PI / (1 << step)));
        for (int i = 0; i < (1 << n); i += (1 << (step + 1))) {
            complex<long double> cur_w(1, 0);
            for (int j = 0; j < (1 << (step)); j++) {
                a[i + j] += cur_w * a[i + j + (1 << step)];
                a[i + j + (1 << step)] = a[i + j] - cur_w * a[i + j + (1 << step)] - cur_w * a[i + j + (1 << step)];
                cur_w *= w;
            }
        }
    }
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    int power_2 = max(a.size(), b.size()), p = 0;
    while (__builtin_popcount(power_2) != 1 || power_2 < a.size() + b.size()) ++power_2;
    while ((1 << p) < power_2) ++p;
    vector<complex<long double>> f(power_2), s(power_2);
    for (int i = 0; i < power_2; i++) {
        if (i < a.size()) f[i] = complex<long double>(a[i], 0);
        if (i < b.size()) s[i] = complex<long double>(b[i], 0);
    }
    bpf(f, p);
    bpf(s, p);
    for (int i = 0; i < power_2; i++) f[i] *= s[i];
    bpf(f, p);
    reverse(f.begin() + 1, f.end());
    vector<int> ans;
    for (auto t : f) ans.push_back(round(t.real() / power_2));
    return ans;
}

int main() {
    string f, s;
    int carry = 0;
    vector<int> a, b;
    cin >> f >> s;
    int plus_minus = (f[0] == '-') ^ (s[0] == '-');
    if (f[0] == '-') f.erase(f.begin());
    if (s[0] == '-') s.erase(s.begin());
    reverse(f.begin(), f.end());
    reverse(s.begin(), s.end());
    for (auto t : f) a.push_back(t - '0');
    for (auto t : s) b.push_back(t - '0');
    vector<int> ans = multiply(a, b);
    for (int i = 0; i < ans.size() || carry; ++i) {
        if (i >= ans.size()) ans.push_back(0);
        ans[i] += carry;
        carry = ans[i] / 10;
        ans[i] %= 10;
    }
    while (ans.back() == 0 && ans.size() > 1) ans.pop_back();
    reverse(ans.begin(), ans.end());
    if (ans[0] != 0 && plus_minus) cout << "-";
    for (auto i : ans) cout << i;
}

