from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



def main():
    n = II()
    xs = LII()
    vs = LII()
    
    l, r = 1e-9, 1e9
    for _ in range(40):
        m = (l * r) ** 0.5
        
        d = Counter()
        for x, v in zip(xs, vs):
            d[x - v * m] += 1
            d[x + v * m] -= 1
        
        cur = 0
        for x in sorted(d):
            cur += d[x]
            if cur == n: r = m; break
        else: l = m
    
    print((l * r) ** 0.5)
    return

if __name__ == "__main__":
    main()