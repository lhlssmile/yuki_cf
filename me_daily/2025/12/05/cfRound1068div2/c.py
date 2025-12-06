from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

t = II()

for _ in range(t):
    n, k = LII()
    a = LII()

    st = set(a)
    good = []
    for v in st:
        ok = True
        t_mul = 1
        while v * t_mul <= k:
            if (v * t_mul) not in st:
                ok = False
                break
            t_mul += 1
        if ok:
            good.append(v)

    min_good_div = {}
    for v in good:
        t_mul = 1
        while v * t_mul <= k:
            m = v * t_mul
            if m in st:
                g = min_good_div.get(m)
                if g is None or v < g:
                    min_good_div[m] = v
            t_mul += 1
    possible = True
    ans_set = set()
    for x in a:
        g = min_good_div.get(x)
        if g is None:
            possible = False
            break
        ans_set.add(g)
    if not possible:
        print(-1)
    else:
        ans = sorted(ans_set)
        print(len(ans))
        print(' '.join(map(str, ans)))
