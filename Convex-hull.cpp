#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct pt {
  long long x, y;
  pt(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
};

bool cmp(pt a, pt b) { return a.x != b.x ? a.x < b.x : a.y < b.y; }

struct Vector {
  long long x, y;
  Vector(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
  Vector(pt a, pt b) : x(b.x - a.x), y(b.y - a.y) {}
};


long long operator*(const Vector &a, const Vector &b) {
  return a.x * b.y - a.y * b.x;
}
bool operator==(const pt &a, const pt &b) { return a.x == b.x && a.y == b.y; }
signed main() {
    long long n;
    cin >> n;
    pt points[n];
    for (long long i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;
    sort(points, points + n, cmp);
    vector<pt> chd, chu;
    chd.push_back(points[0]), chd.push_back(points[1]);
    chu.push_back(points[0]), chu.push_back(points[1]);
    for (long long i = 2; i < n; i++) {
        while ((chd.size() >= 2 && Vector(chd[chd.size() - 2], chd.back()) *
                Vector(chd.back(), points[i]) <= 0) ||
                (chd.size() >= 1 && chd.back() == points[i]))
            chd.pop_back();
    chd.push_back(points[i]);
    while ((chu.size() >= 2 && Vector(chu[chu.size() - 2], chu.back()) *
            Vector(chu.back(), points[i]) >= 0) ||
           (chu.size() >= 1 && chu.back() == points[i]))
        chu.pop_back();
    chu.push_back(points[i]);
    }
    chu.pop_back();
    vector<pt> ans;
    for (pt p : chd) ans.push_back(p);
    for (long long i = chu.size() - 1; i >= 1; i--) ans.push_back(chu[i]);
    long long sans = 0;
    long double per = 0;
    n = ans.size();
    for (long long i = 0; i < n; i++) {
        sans += Vector(pt(0, 0), ans[i]) * Vector(pt(0, 0), ans[(i + 1) % n]);
        per += sqrt((long double) ((Vector(ans[i], ans[(i + 1) % n]).x *
                 Vector(ans[i], ans[(i + 1) % n]).x) +
                (Vector(ans[i], ans[(i + 1) % n]).y *
                 Vector(ans[i], ans[(i + 1) % n]).y)));
    }
    cout << per << "\n";
    if (sans % 2 == 0) cout << sans / 2;
    else cout << sans / 2 << ".5";
}
