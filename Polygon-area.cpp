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
    long long sans = 0;
    for (long long i = 0; i < n; i++) {
        sans += Vector(pt(0, 0), points[i]) * Vector(pt(0, 0), points[(i + 1) % n]);
    }
    if (sans % 2 == 0) cout << abs(sans / 2);
    else cout << abs(sans / 2) << ".5";
}
