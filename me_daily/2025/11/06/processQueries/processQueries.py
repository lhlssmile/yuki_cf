from collections import defaultdict
from typing import List
import sys
import heapq
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



def processQueries(c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:
    graph = [[] * (c + 1)]

    for u, v in connections:
        graph[u].append(v)
        graph[v].append(u)
    belong = [-1] * (c + 1)
    ans = []
    heaps = []
    offline = [False] * (c + 1)
    def dfs(x: int) -> None:
        belong[x] = len(heaps)
        h.append(x)
        for y in graph[x]:
            if belong[y] < 0:
                dfs(y)
    for i in range(1, c + 1):
        if belong[i] >= 0:continue
        h = []
        dfs(i)
        heapq.heapify(h)
        heaps.append(h)

    for st, x in queries:
        if st == 2: offline[x] = True; continue
        if not offline[x]: ans.append(x); continue
        h = heaps[belong[x]]
        while h and offline[h[0]]:
            heapq.heappop(h)
        ans.append(h[0] if h else -1)
    return ans


c = II()
connectionL = LII()
connections = []
for _ in range(connectionL):
    u, v = LII()
    connections.append((u, v))
queriesL = II()
queries = []
for _ in range(queriesL):
    st, sta = LII()
    queries.append((st, sta))

ans = processQueries(c, connections, queries)
print(*ans)