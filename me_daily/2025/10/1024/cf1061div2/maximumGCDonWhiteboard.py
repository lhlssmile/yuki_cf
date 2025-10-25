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
    n, k = LII()
    a = LII()
    freq = [0] * (n + 1)
    for x in a:
        freq[x] += 1
    prefix = [0] * (n + 1)
    for i in range(1, n + 1):
        prefix[i] = prefix[i - 1] + freq[i]
    ans = 1
    for d in range(n, 0, -1):
        up = min(n, 4 * d - 1)
        num_small = prefix[up]
        num_small_good = 0
        for m in range(1, 4):
            val = m * d
            if val > n:
                break
            num_small_good += freq[val]
        cost = num_small - num_small_good
        if cost <= k:
            ans = d
            break
    print(ans)