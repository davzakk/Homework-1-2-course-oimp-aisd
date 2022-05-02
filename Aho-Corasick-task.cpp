#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    node *g[2], *aut[2], *p, *link, *term_link;
    int id, c, term;
};

const int INF = 1e6;
node aho[INF];
int counter = 0;

node *new_node() {
    aho[counter].id = counter;
    return aho + counter++;
}

void add_t(const string &s) {
    node *v = aho;
    for (auto &i : s) {
        int c = (i - '0');
        if (v->g[c] == nullptr) {
            v->g[c] = new_node();
            v->g[c]->p = v;
            v->g[c]->c = c;
        }
        v = v->g[c];
    }
    v->term++;
}

node *go(node *v, int c);

node *link(node *v) {
    if (v->link != nullptr) return v->link;
    if (v == aho || v->p == aho) return v->link = aho;
    v->link = go(link(v->p), v->c);
    return v->link;
}

node *go(node *v, int c) {
    if (v->aut[c] != nullptr) return v->aut[c];
    if (v->g[c] != nullptr) return v->aut[c] = v->g[c];
    if (v == aho) return v->aut[c] = aho;
    v->aut[c] = go(link(v), c);
    return v->aut[c];
}

node *terminal(node *v) {
    if (v->term_link != nullptr) return v->term_link;
    if (v == aho) return v->term_link = v;
    if (link(v)->term > 0) return v->term_link = link(v);
    v->term_link = terminal(link(v));
    return v->term_link;
}

int used[INF];

void dfs(node *v) {
    used[v->id] = 1;
    for (int i = 0; i < 2; ++i) {
        node *u = go(v, i);
        if (terminal(u) != aho || u->term) continue;
        if (used[u->id] == 1) {
            cout << "TAK";
            exit(0);
        } else if (used[u->id] == 0) dfs(u);
    }
    used[v->id] = 2;
}

signed main() {
    int n;
    cin >> n;
    node *root = new_node();
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add_t(s);
    }
    dfs(root);
    cout << "NIE";
}
