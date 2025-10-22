

from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


t = II()
for _ in range(t):
    n = II()
    a = LII()
    m = [0] * (n + 1)
    m[1] = a[0]
    # 0 1 2 3 4    0 1 2 3 4 5
    # 1 4 2 5 3 -> 0 1 4 4 5 5
    for i in range(1, n): m[i + 1] = max(m[i], a[i])

    ans = 0

    for i in range(0, n, 2):
        if i == 0:
            u = m[2] - 1
            b = min(a[i], max(0, u))
            ans += a[i] - b
        elif i == n - 1:
            u = m[i] - 1
            b = min(a[i], max(0, u))
            ans += a[i] - b
        else:
            u = min(m[i + 2], m[i]) - 1
            b = min(a[i], max(0, u))
            ans += a[i] - b
    print(ans)