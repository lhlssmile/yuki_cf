from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def main():
    n = II()
    a = LII()
    o = a.count(1)
    if o > 0:
        return n - o
    
    g = a[0]
    for i in range(1,n):
        g = gcd(g, a[i])
    if g > 1: return -1;
    best = float('inf')
    for i in range(n):
        g = a[i]
        for j in range(i, n):
            g = gcd(g, a[j])
            if g == 1:
                best = min(best, j - i + 1)
                break
    return (n - 1) + best - 1
if __name__ == "__main__":
    print(main())

