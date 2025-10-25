from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
fmin = lambda a, b: a- b

def main(): 
    n, m = LII()
    grid = [[1 if c == '#' else 0 for c in I()] for _ in range(n)]
    total = sum(sum(x) for x in grid)
    
    tmp = [[0] * m for _ in range(n)]
    
    for i in range(fmin(n, m), 0, -1):
        if total % (i * i) == 0:
            for x in range(n):
                for y in range(m):
                    tmp[x][y] = grid[x][y]
            
            flg = True
            for x in range(n):
                for y in range(m):
                    if tmp[x][y]:
                        for dx in range(x, x + i):
                            for dy in range(y, y + i):
                                if dx >= n or dy >= m or tmp[dx][dy] == 0:
                                    flg = False
                                    break
                                tmp[dx][dy] = 0
                            if not flg: break
                        if not flg: break
                if not flg: break
            
            if flg:
                print(i)
                break

if __name__ == "__main__":
    main()