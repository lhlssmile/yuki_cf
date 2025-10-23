from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


n, a, b = LII()
k1 = n // 2
k2 = n - k1

v1, v2 = [0] * k1, [0] * k2

for i in range(k1):
    m, t = LII()
    v1[i] = m * b - a * t
for i in range(k2):
    m, t = LII()
    v2[i] = m * b - a * t

mp = defaultdict(int)

for mask in range(1 << k1):
    val = 0
    for j in range(k1):
        if mask & (1 << j): val += v1[j]
    mp[val] += 1

ans = 0
for mask in range(1 << k2):
    val = 0
    for j in range(k2):
        if mask & (1 << j): val += v2[j]
    ans += mp[-val]
ans -= 1   # 空集被算了一次
print(ans)