from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

class Fenwick:
    def __init__(self,n):
        self.n = n
        self.tree = [0] * (n + 1)
    def add(self, i,v):
        while i <= self.n:
            self.tree[i] += v
            i += i & -i
    def sum(self, i):
        s = 0
        while i > 0:
            s += self.tree[i]
            i -= i & -i
        return s
    def range_sum(self, l, r):
        if l > r: return 0
        return self.sum(r) - self.sum(l - 1)

n, k = LII()
a = LII()

vals = sorted(a)
unique_vals = []
for x in vals: 
    if not unique_vals or x != unique_vals[-1]: unique_vals.append(x)
vals = unique_vals
m = len(vals)
rank = [vals.index(num) + 1 for num in a]
ft = Fenwick(m)


cur_inv = 0

for i in range(k):
    cur_inv += ft.range_sum(rank[i] + 1, m) 
    ft.add(rank[i], 1)

min_inv = cur_inv

for i in range(k, n):
    oldL = i - k
    cur_inv -= ft.range_sum(1, rank[oldL] - 1)
    ft.add(rank[oldL],-1)
    cur_inv += ft.range_sum(rank[i] + 1, m)
    ft.add(rank[i], 1)
    min_inv = min(min_inv, cur_inv)
print(min_inv)