from typing import List
import sys

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()

def solve(n: int, s: str, queries: List[int]) -> List[int]:
    all_a = True
    for c in s:
        if c == 'B':
            all_a = False
            break
    res = []
    if all_a:
        for qi in queries:
            res.append(qi)
        return res
    
    chain = [0] * n
    for i in range(n):
        if s[i] == 'B':
            continue
        p, clen = i, 0
        while clen < n and s[p] == 'A':
            clen += 1
            p = (p + 1) % n
        chain[i] = clen
    
    for qi in queries:
        x = qi
        pos = 0
        steps = 0
        while x > 0:
            if s[pos] == 'B':
                x //= 2
                steps += 1
                if x == 0:
                    break
                pos = (pos + 1) % n
            else:
                clen = chain[pos]
                if x <= clen:
                    steps += x
                    x = 0
                    break
                else:
                    steps += clen
                    x -= clen
                    pos = (pos + clen) % n
        res.append(steps)
    return res

t = II()
for _ in range(t):
    n, q = LII()
    s = SI()
    queries = LII()
    ans = solve(n, s, queries)
    for v in ans: print(v)