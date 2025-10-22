from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def solve(s, k):
    n = len(s)
    ans = 0
    last = -k
    for i in range(n):
        if s[i] == '1':
            if i - last >= k:
                ans += 1
                last = i
            else:
                last = i
    return ans

t = II()
for _ in range(t):
    n, k = LII() 
    s = SI()      
    print(solve(s, k))