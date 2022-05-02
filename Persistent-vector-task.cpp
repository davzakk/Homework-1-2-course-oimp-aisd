#include <iostream>
#include <vector>
#include <algorithm>
#define int int64_t
using namespace std;

struct Node {
    int value = -1;
    Node* prev;
    vector<Node*> kids;
    int ends_counter = 1;
};

vector<Node*> vec;

void push(Node* i, int x) {
    Node* k = new Node();
    k->value = x;
    k->prev = i;
    i->kids.push_back(k);
    vec.push_back(k);
}
void pop(Node* i) {
    ++i->prev->ends_counter;
    vec.push_back(i->prev);
}

int ans = 0, cur = 0;
void dfs(Node* v) {
    cur += v->value;

    ans += cur * v->ends_counter;
    for (Node* u : v->kids) {
        dfs(u);
        delete u;
    }

    cur -= v->value;
}
signed main() {
    Node* nod = new Node();
    nod->value = 0;
    vec.push_back(nod);
    int n, t, m;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> t >> m;
        if (m) push(vec[t], m);
        else pop(vec[t]);
    }
    dfs(vec[0]);
    delete vec[0];
    cout << ans;
}
