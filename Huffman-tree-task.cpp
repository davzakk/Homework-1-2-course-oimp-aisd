#define _GLIBCXX_DEBUG

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Node {
    Node *l = nullptr;
    Node *r = nullptr;
    string val;
    Node *p = nullptr;
};

Node *insert(Node *tree, Node *parent, int who) {
    tree = new Node();
    tree->p = parent;
    if (who == 1) {tree->val = tree->p->val; tree->val += '0';}
    else  {tree->val = tree->p->val; tree->val += '1';}
    return tree;
}

vector<string> ans;

void bypass(Node *tree) {
    if (tree != nullptr) {
        bypass(tree->l);
        if (tree->l == nullptr && tree->r == nullptr)
            ans.push_back(tree->val);
        bypass(tree->r);
    }
}

Node *up(Node *tec) {
    while (tec->p != nullptr) {
        tec = tec->p;
    }
    return tec;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Node *tree = new Node();
        Node *tec = tree;
        tec->val = "";
        string s;
        ans.clear();
        cin >> s;
        for (char j: s) {
            if (j == 'D') {
                if (tec->l == nullptr) {
                    tec->l = insert(tec->l, tec, 1);
                    tec = tec->l;
                } else {
                    tec->r = insert(tec->r, tec, 2);
                    tec = tec->r;
                }
            } else {
                while (tec->p->r == tec) tec = tec->p;
                if (tec->p != nullptr) {
                    tec = tec->p;
                    if (tec->r == nullptr) tec->r = insert(tec->r, tec, 2);
                    tec = tec->r;
                }
            }
        }
        bypass(up(tec));
        cout << ans.size() << "\n";
        for (const auto &j: ans) cout << j << "\n";
    }
}
