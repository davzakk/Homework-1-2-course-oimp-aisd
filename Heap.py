heap = []

def minn():
    global heap
    return heap[0]

def sift_up(i):
    global heap
    while i > 0 and heap[(i - 1) // 2] > heap[i]:
        heap[(i - 1) // 2], heap[i] = heap[i], heap[(i - 1) // 2]
        i = (i - 1) // 2

def sift_down(i, n):
    global heap
    while True:
        min_position = i
        if 2 * i + 1 < n and heap[2 * i + 1] < heap[min_position]:
            min_position = 2 * i + 1
        if 2 * i + 2 < n and heap[2 * i + 2] < heap[min_position]:
            min_position = 2 * i + 2
        if min_position == i:
            break
        heap[i], heap[min_position] = heap[min_position], heap[i]
        i = min_position

def insert(x): # O(log n)
    global heap
    heap.append(x)
    i = len(heap) - 1
    sift_up(i)
    
def remove_min(): # O(log n)
    global heap
    heap[0], heap[-1] = heap[-1], heap[0]
    heap.pop()
    i = 0
    n = len(heap)
    sift_down(i, n)


n = int(input())
heap = []
for i in range(n):
    s = input().split()
    if s[0] == 'push':
        val = -int(s[1])
        insert(val)
    elif s[0] == 'pop':
        print(-minn())
        remove_min()
    elif s[0] == 'get':
        val = int(s[1])
        print(-heap[val])
