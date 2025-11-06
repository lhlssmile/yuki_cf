import sys

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))

T = II()
for _ in range(T):
    n, k_max = LII()
    s = input()
    t = input()

    if s == t:
        print(0)
        continue

    last = [-1] * 26
    k = 0
    possible = True
    for i in range(n):
        last[ord(s[i]) - 97] = i
        j = last[ord(t[i]) - 97]
        if j == -1:
            possible = False
            break
        k = max(k, i - j)

    if (not possible) or k > k_max:
        print(-1)
        continue

    print(k)
    # compute source index p[i] and distance d[i]
    last = [-1] * 26
    p = [0] * n
    d = [0] * n
    for i in range(n):
        last[ord(s[i]) - 97] = i
        p[i] = last[ord(t[i]) - 97]
        d[i] = i - p[i]

    # build schedule: at step r copy at positions j = p[i] + r (1 <= r <= d[i])
    sched = [[] for _ in range(k + 1)]  # 0 unused
    for i in range(n):
        for r in range(1, d[i] + 1):
            j = p[i] + r
            sched[r].append(j)

    cur = list(s)
    tgt = list(t)
    for r in range(1, k + 1):
        need_copy = [False] * n
        for j in sched[r]:
            if 0 <= j < n:
                need_copy[j] = True
        nxt = cur[:]
        for j in range(1, n):
            if need_copy[j] or cur[j] != tgt[j]:
                nxt[j] = cur[j - 1]
        print(''.join(nxt))
        cur = nxt

