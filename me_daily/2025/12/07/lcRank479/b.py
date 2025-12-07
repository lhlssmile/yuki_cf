from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
import math
MX = 5 * 10 ** 5
primes = []
is_prime = [True] * (MX + 1)
ans = [0] * (MX + 1)
n = II()
def prehandle():
    is_prime[0] = is_prime[1] = False
    for i in range(2, MX + 1):
        if is_prime[i]:
            primes.append(i)
            for j in range(i*i,MX+1, i):
                is_prime[j] = False
    
    s,last,j = 0,0,0
    for i in range(2,MX+1):
        if s + primes[j] <= i:
            s += primes[j]
            j += 1
            if is_prime[s]: last = s
        ans[i] = last

prehandle()
print(ans[n])