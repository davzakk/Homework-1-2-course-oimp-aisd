def merge(a, b):
    c = []
    aa = a
    bb = b
    q, w = 0, 0
    while q != len(aa) and w != len(bb):
        if aa[q] < bb[w]:
            c.append(aa[q])
            q += 1
        else:
            c.append(bb[w])
            w += 1
    c += aa[q:] + bb[w:]
    return c

def merge_sort(mas):
    if len(mas) == 1:
        return mas
    x = merge_sort(mas[0:(len(mas) + 1) // 2])
    y = merge_sort(mas[(len(mas) + 1) // 2:])
    return merge(x, y)

n = int(input())
mas = list(map(int, input().split()))
merge_sort(mas)
