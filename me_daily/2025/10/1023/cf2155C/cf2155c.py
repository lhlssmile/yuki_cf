MOD = 676767677
from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
def solve(n, a):
    if n == 1:
        return 2 if a[0] == 1 else 0
    
    s = []
    for i in range(n-1):
        d = a[i] - a[i+1]
        si = 1 - d
        if si < 0 or si > 2:
            return 0
        s.append(si)
    
    ways = 0
    for start in [0, 1]:
        x = [0] * n
        x[0] = start
        valid = True
        for i in range(n-1):
            next_x = s[i] - x[i]
            if next_x not in (0, 1):
                valid = False
                break
            x[i+1] = next_x
        if valid:
            S = sum(x[:n-1])  # 前n-1个x的和
            implied_an = 1 + S
            if implied_an == a[n-1]:
                ways += 1
    return ways % MOD

if __name__ == "__main__":
    t = II()
    for _ in range(t):
        n = II()
        a = LII()
        print(solve(n, a))
