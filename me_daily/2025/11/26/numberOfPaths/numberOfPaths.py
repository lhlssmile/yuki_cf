from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
from functools import cache
m,n,k = LII()
grid = [LII() for _ in range(m)]
MOD = 10 ** 9 + 7

@cache
def dfs(i,j,s):
    if i < 0 or j < 0: return 0
    pres = (s - grid[i][j]) % k
    if i == 0 and j == 0:
        return 1 if pres == 0 else 0
    return (dfs(i - 1,j,pres) + dfs(i,j-1,pres)) % MOD

print(dfs(m - 1, n - 1, 0))
dfs.cache_clear()


