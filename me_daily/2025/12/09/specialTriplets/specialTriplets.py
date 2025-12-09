from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



n = II()
a = LII()
MOD = 10 ** 9 + 7
MX = 200010
freq_right = [0] * MX
right = [0] * n
for j in range(n - 1, 0, -1):
    target = a[j]<<1
    if target < MX:
        right[j] = freq_right[target]
    if a[j] < MX: freq_right[a[j]] += 1
freq_left = [0] * MX
ans = 0
for j in range(n):
    target = a[j] << 1
    left_cnt = 0
    if target < MX:left_cnt = freq_left[target]
    contrib = (left_cnt * right[j]) % MOD
    ans = (ans + contrib) % MOD

    if a[j] < MX:freq_left[a[j]]+=1
print(ans)
