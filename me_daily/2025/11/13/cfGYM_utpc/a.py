from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

MOD = 10 ** 9 + 7

n = II()


a = LII()

ans = 0


i = 0
while i < n:
    if a[i] == 0:
        i += 1
        continue
    cur = 1
    while i < n and a[i] != 0:
        cur = (cur * a[i]) % MOD
        i += 1
    ans = (ans + cur) % MOD
print(ans)
