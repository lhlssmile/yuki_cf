from collections import defaultdict
from typing import List
import sys
import math

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

h, w = LII()
a = [list(SI()) for _ in range(h)]  

def solve(h: int, w: int, a: List[List[str]]) -> None:
    total = sum(1 for i in range(h) for j in range(w) if a[i][j] == '#')
    if total == 0:
        print(0)
        return
    prefix = [[0] * (w + 1) for _ in range(h + 1)]
    for i in range(h):
        for j in range(w):
            val = 1 if a[i][j] == '#' else 0
            prefix[i + 1][j + 1] = prefix[i][j + 1] + prefix[i + 1][j] - prefix[i][j] + val
    def rect_sum(r1, c1, r2, c2):
        return prefix[r2][c2] - prefix[r1 - 1][c2] - prefix[r2][c1 - 1] + prefix[r1 - 1][c1 - 1]
    divs = [i for i in range(1, int(math.sqrt(total)) + 1) if total % i == 0]
    divs += [total // i for i in divs if i != total // i]  # 补对称因子
    divs.sort()
    poss_s = []
    mn = min(h, w)
    for d in divs:
        s = int(math.sqrt(d)) 
        if s * s == d and 1 <= s <= mn:
            poss_s.append(s)
    poss_s.sort(reverse=True) 
    def can_tile(s):
        covered = [[False] * w for _ in range(h)]
        for i in range(h):
            for j in range(w):
                if a[i][j] != '#' or covered[i][j]: continue
                if i + s > h or j + s > w: return False
                r1, c1, r2, c2 = i + 1, j + 1, i + s, j + s
                if rect_sum(r1, c1, r2, c2) != s * s: return False
                ok = True
                for di in range(s):
                    if not ok: break
                    for dj in range(s):
                        if covered[i + di][j + dj]:
                            ok = False
                            break
                if not ok: return False
                for di in range(s):
                    for dj in range(s): 
                        covered[i + di][j + dj] = True
        return True 
    for p in poss_s:
        if can_tile(p): 
            print(p)
            return 
    print(1)

solve(h, w, a) 