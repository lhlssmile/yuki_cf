from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


n = II()
a = [0] + LII()
b = [0] + LII()

def gcd(a,b):
    while b:
        a, b = b, a % b
    return a


def get_primes(x)->List[int]:
    res = []

    i = 2

    while i * i <= x:
        if x % i == 0:
            res.append(i)
            while x % i == 0:
                x //= i
        i += 1
    if x > 1:
        res.append(x)
    return res
g = a[1]

for i in range(2,n+1):
    g = gcd(g,a[i])
if g == 1: print(0);exit(0)



primes = get_primes(g)
k = len(primes)

INF = 1 << 60

covers = [0] * (n + 1)

for i in range(1, n + 1):
    mask = 0
    for j in range(k):
        p = primes[j]
        if b[i] % p != 0:
            mask |= (1 << j)
    covers[i] = mask

dp = [INF] * (1 << k)

dp[0] = 0

for i in range(1, n + 1):
    cost = i * (i + 1)
    mask_i = covers[i]
    new_dp = dp[:]

    for prev in range(1 << k):
        if dp[prev] == INF:
            continue
        newm = prev | mask_i
        new_dp[newm] = min(new_dp[newm],dp[prev] + cost)
    dp = new_dp
full = (1 << k) - 1
ans = dp[full]
print(-1 if ans == INF else ans)