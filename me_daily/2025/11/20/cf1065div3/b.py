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
    n = II()
    a = LII()
    b = a[:]
    if b[0] == -1 and b[-1] == -1:
        b[0] = 0
        b[-1] = 0
    elif b[0] == -1:
        b[0] = b[-1]
    elif b[-1] == -1:
        b[-1] = b[0]
    for i in range(1, n - 1):
        if b[i] == -1:
            b[i] = 0
    ans = abs(b[-1] - b[0])
    print(ans)
    print(*b)