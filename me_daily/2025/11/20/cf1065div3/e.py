from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

'''
9
6
1 3 4 5 2 6
4
3 4 1 2
5
4 3 5 1 2
4
1 2 3 4
7
4 3 5 7 6 2 1
6
2 4 6 1 3 5
3
2 1 3
4
2 4 1 3
6
4 2 6 5 1 3


out
Yes
No
No
Yes
No
Yes
Yes
Yes
Yes

'''



t = II()

for _ in range(t):
    n = II()
    a = LII()
    pos = [0] * (n + 1)
    for i, v in enumerate(a, 1):
        pos[v] = i
    pre_min = [10**9] * (n + 1)
    suf_max = [0] * (n + 2)
    for k in range(1, n + 1):
        pre_min[k] = min(pre_min[k - 1], pos[k])
    for k in range(n, 0, -1):
        suf_max[k] = max(suf_max[k + 1], pos[k])
    ok = True
    for k in range(1, n):
        if suf_max[k + 1] < pre_min[k]:
            ok = False
            break
    print("Yes" if ok else "No")
