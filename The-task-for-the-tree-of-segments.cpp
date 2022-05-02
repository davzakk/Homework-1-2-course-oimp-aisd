n = int(input())
mas = list(map(int, input().split()))
k = int(input())
tree = [0] * (4 * n)


def build(l, r, v):
    global mas, tree
    if l + 1 == r:
        tree[v] = [mas[l], l]
    else:
        m = (l + r) // 2
        build(l, m, 2 * v)
        build(m, r, 2 * v + 1)
        tree[v] = max(tree[2 * v], tree[2 * v + 1])


def get(l, r, tl, tr, v):
    global tree
    if r <= tl or l >= tr:
        return [-1e10, -1]
    if l <= tl and tr <= r:
        return tree[v]
    else:
        m = (tl + tr) // 2
        return max(get(l, r, tl, m, 2 * v), get(l, r, m, tr, 2 * v + 1))


def update(ind, val, tl, tr, v):
    global tree
    if tl + 1 == tr:
        tree[v] = [val, tree[v][1]]
    else:
        m = (tl + tr) // 2
        if ind < m:
            update(ind, val, tl, m, 2 * v)
        else:
            update(ind, val, m, tr, 2 * v + 1)
        tree[v] = max(tree[2 * v], tree[2 * v + 1])


build(0, n, 1)
for i in range(k):
    t, l, r = map(int, input().split())
    if t == 1:
        print(get(l, r + 1, 0, n, 1)[1])
    else:
        update(l, r, 0, n, 1)
