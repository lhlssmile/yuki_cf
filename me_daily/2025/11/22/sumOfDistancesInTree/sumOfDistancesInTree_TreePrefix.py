from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



n, e = LII()
edges = [LII() for _ in range(e)]

# print(*edges)
g = [[] for _ in range(n)]
for u, v in edges:
    g[u].append(v)
    g[v].append(u)
# print(*g)
ans = [0] * n
# sz[u]:以u为根的子树节点数(包括自己)
sz_ = [0] * n
total_dist = [0]
def dfs_d(u, p, d):
    total_dist[0] += d
    sz_[u] = 1
    for v in g[u]:
        if v != p:
            dfs_d(v, u, d + 1)
            sz_[u] += sz_[v]

dfs_d(0, -1, 0)  # u:0 假父-1?
# print(*sz_)
ans[0] = total_dist[0]
# print(ans[0])


def dfs_c(u, p, curr_ans):
    ans[u] = curr_ans
    for v in g[u]:
        if v != p:
            new_ans = curr_ans + n - 2 * sz_[v]
            dfs_c(v, u, new_ans)
dfs_c(0, -1, ans[0])
print(*ans)