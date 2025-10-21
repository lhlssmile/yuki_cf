from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



n = II()
k = II()
op = II()

a = LII()

cnt = defaultdict(int)
diff = defaultdict(int)

for x in a:
    cnt[x] += 1
    diff[x]
    diff[x - k] += 1
    diff[x + k + 1] -= 1
ans = sumd = 0
for x, d in sorted(diff.items()):
    sumd += d
    ans = max(ans, min(sumd, op + cnt[x]))

print(ans)