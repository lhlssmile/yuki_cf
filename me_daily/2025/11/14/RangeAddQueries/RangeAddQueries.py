from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



n, q = LII()

grid = [[0] * n for _ in range(n)]

queries = [LII() for _ in range(q)]

diff = [[0] * (n + 2) for _ in range(n + 2)]

for r1, c1, r2, c2 in queries:
            diff[r1 + 1][c1 + 1] += 1
            diff[r1 + 1][c2 + 2] -= 1
            diff[r2 + 2][c1 + 1] -= 1
            diff[r2 + 2][c2 + 2] += 1

for i in range(n):
    for j in range(n):
        diff[i + 1][j + 1] += diff[i + 1][j] + diff[i][j + 1] - diff[i][j]
        grid[i][j] = diff[i + 1][j + 1]

print(*grid)


