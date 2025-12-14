from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


corridor = SI()
MOD = 10 ** 9
pos_s = [i for i in range(len(corridor)) if corridor[i] == 'S']
m = len(pos_s)
ans = 0
for k in range(1,m//2):
     ans += (pos_s[k<<1] - pos_s[(k<<1) - 1])%MOD
print(ans)