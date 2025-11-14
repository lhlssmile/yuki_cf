from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


n, m = LII()

grid = [LII() for _ in range(n)]

f = [[0] * (m + 1) for _ in range(n + 1)]

ans = 0

for i in range(1, n + 1):
    for j in range(1, m + 1):
        if grid[i - 1][j - 1] == 1:
            f[i][j] = min(f[i - 1][j - 1], f[i][j - 1], f[i - 1][j]) + 1
            ans = max(ans, f[i][j])
print(ans)