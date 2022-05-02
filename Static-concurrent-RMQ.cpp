#include <vector>
#include <future>
#include <algorithm>
#include <execution>
#include <iostream>
#include <set>

using namespace std;

struct Request { int left; int right; };
vector<int> t;

void recalc(int v) {
    t[v] = min(t[v * 2], t[v * 2 + 1]);
}

void upd(int v, int l, int r, int L, int R, int x) {
    if (l >= R || L >= r) return;
    if (L <= l && r <= R) {
        t[v] = x;
        return;
    }
    upd(v * 2, l, (l + r) / 2, L, R, x);
    upd(v * 2 + 1, (l + r) / 2, r, L, R, x);
    recalc(v);
}

int get(int v, int l, int r, int L, int R) {
    if(l >= R || L >= r) return 1e9;
    if(L <= l && r <= R) return t[v];

    return min(get(v * 2, l, (l + r) / 2, L, R), get(v * 2 + 1, (l + r) / 2, r, L, R));
}


void build(const vector<int>& numbers, int v, int l, int r) {
    if (l == r) {
        t[v] = numbers[l];
    } else {
        int m = (l + r) / 2;
        build(numbers, 2 * v, l, m);
        build(numbers, 2 * v + 1, m + 1, r);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
}

void do_requests(int L, int R, int n, const vector<Request>& requests, vector<int>& ans) {
    for(int i = L; i < R; ++i) {
        int l = requests[i].left, r = requests[i].right;
        ans[i] = get(1, 0, n, l, r);
    }
}

vector<int> ProcessRequests(const vector<int>& numbers, const vector<Request>& requests) {
    vector<int> s = {1};
    vector<int> numbers2(numbers);
    while (s.back() < numbers2.size()) {
        s.push_back(s.back() * 2);
    }
    int num_sz = numbers2.size();
    for (int i = 0; i < s.back() - num_sz; ++i) {
        numbers2.push_back(1e9);
    }
    int n = numbers2.size(), m = requests.size();
    vector<int> ans(m);
    t.resize(4 * n, 1e9);
    build(numbers2, 1, 0, n - 1);
    auto f1 = async([&] { do_requests(0, m / 2, n, requests, ans); });
    do_requests(m / 2 * 1, m, n, requests, ans);
    f1.get();
    return ans;
}
