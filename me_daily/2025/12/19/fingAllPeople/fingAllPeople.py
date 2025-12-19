from collections import defaultdict, deque
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px != py:
            if self.rank[px] < self.rank[py]:
                self.parent[px] = py
            elif self.rank[px] > self.rank[py]:
                self.parent[py] = px
            else:
                self.parent[py] = px
                self.rank[px] += 1

def main():
    n, m,f_p = LII()
    meetings = []
    for _ in range(m):
        meetings.append(LII())
    uf = UnionFind(n)
    uf.union(0,f_p)
    know_roots = {uf.find(0)}
    meetings.sort(key=lambda x: x[2])
    i = 0
    while i < m:
        cur_time = meetings[i][2]
        group = []
        while i < m and meetings[i][2] == cur_time:
            x, y, _ = meetings[i]
            group.append((x, y))
            i += 1
        if not group: continue

        adj = defaultdict(list)
        involed = set()

        for x, y in group:
            adj[x].append(y)
            adj[y].append(x)
            involed.add(x)
            involed.add(y)
        
        visited = set()
        queue = deque()

        for person in involed:
            if uf.find(person) in know_roots and person not in visited:
                queue.append(person)
                visited.add(person)
        while queue:
            u = queue.popleft()
            for v in adj[u]:
                if v not in visited:
                    visited.add(v)
                    queue.append(v)
                    uf.union(u,v)
        for p in visited:
            know_roots.add(uf.find(p))
        

    result = sorted([j for j in range(n) if uf.find(j) in know_roots])
    print(' '.join(map(str, result)))  # 输出排序列表，空格分隔
    
if __name__ == "__main__":
    main()  