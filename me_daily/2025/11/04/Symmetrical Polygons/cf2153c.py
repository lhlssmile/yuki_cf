from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

# 建垚

t = II()
for _ in range(t):
    n = II()
    a = LII()
    cnt = Counter(a)
    base = 0
    odd, even = [], []
    for x, c in cnt.items():
        base += (c // 2) * x
        if c % 2 == 1:
            odd.append(x)
        elif c >= 2:
            even.append(x)
    
    if base == 0:
        print(0)
        continue
    
    ans = 0
    for x in odd: 
        if 2 * base > x:
            ans = max(ans, 2 * base + x)
    odd.sort()
    for i in range(1, len(odd)):
        if odd[i - 1] + 2 * base > odd[i]: ans = max(ans, odd[i - 1] + 2 * base + odd[i])

    for x in even: 
        if base - x > 0:
            ans = max(ans, 2 * base)
    print(ans)