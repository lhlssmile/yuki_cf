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
        self.tree = [0] * (n+2)
    def update(self, i, v):
        while i <= self.n:
            self.tree[i] += v
            i += i & -i

    def query(self, i:int)->int:
        s = 0
        while i > 0:
            s += self.tree[i]             
            i -= i & -i
        return s
    
    def range(self,l,r):
        if l == r: return 0
        
        return self.query(r) - self.query(l)
n, q = LII()
s = SI()
s = list(s)
queries = []
for _ in range(q):
    all = LII()
    if all[0] == 1:
        queries.append((1, all[1]))
    else:
        queries.append((2, all[1],all[2]))
ft = Fenwick(n - 1)
bad = [0] * (n+1)
for i in range(1,n):
    bad[i] = 1 if s[i] == s[i-1] else 0
    ft.update(i,bad[i])

ans = []
for qi in queries:
    if qi[0] == 1:
        j = qi[1]
        # 算旧的和更新?
        old_sj = s[j]
        s[j] = 'A' if old_sj == 'B' else 'B'
        for pos in [j, j + 1]:
            if 1 <= pos < n:
                old = bad[pos]
                new = 1 if s[pos] == s[pos-1] else 0
                if old != new:
                    bad[pos] = new
                    ft.update(pos, new - old)
    else:
        # 用公式来计算最小删除数
        l,r = qi[1],qi[2]
        sub_len = r - l + 1
        if sub_len == 1:ans.append(0);continue
        ans.append(ft.query(r) - ft.query(l))
print(*ans)

