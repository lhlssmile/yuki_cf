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

    freq = Counter(a)
    odd_cnt = sum(1 for c in freq.values() if c&1)
    even_cnt = sum(1 for c in freq.values() if c % 2 == 0 and c > 0)
    base = odd_cnt
    if odd_cnt>0:
        extra = even_cnt << 1
    else:
        parity_need = n % 2
        mx_k = even_cnt if (even_cnt % 2 == parity_need) else even_cnt - 1
        extra = 2 * mx_k
    print(base + extra)