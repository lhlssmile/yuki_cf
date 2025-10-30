from collections import defaultdict
from typing import List
import sys
import heapq
from collections import deque
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()




n, m, k = LII()
adj = [[] for _ in range(n + 1)]
edges = []
for _ in range(m):
    x, y, c = LII()
    edges.append((x, y, c))
    adj[x].append((y, c))
    adj[y].append((x, c))

inf = 10 ** 18

dis = [inf] * (n + 1)
dis[1] = 0

pq = [(0, 1)]
heapq.heapify(pq)

while pq:
    d, u = heapq.heappop(pq)
    if d > dis[u]: continue
    for v, c in adj[u]:
        if dis[v] > dis[u] + c:
            dis[v] = dis[u] + c
            heapq.heappush(pq, (dis[v], v))

sp_sum = dis[n]
vis = [False] * (n + 1)
q = deque([1])

while q:
    u = q.popleft()
    for v, _ in adj[u]:
        if not vis[v]:
            vis[v] = True
            q.append(v)

cost = []
for x, y, c in edges:
    if vis[x] and vis[y]:
        cost.append(c)

cost.sort()
t = min(k, len(cost))

start2 = sum(cost[:t])

print(min(sp_sum, start2))



 