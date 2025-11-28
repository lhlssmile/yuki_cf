from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


def main():
    n, e, k =LII()
    g = [[] * n for _ in range(n)]
    edges = [LII() for _ in range(e)]
    values = LII()

    for u, v in edges:
        g[u].append(v)
        g[v].append(u)


    '''
    要算每个可能的连通分量和(点权?)怎么快速得出?
    '''
    prefix_ = [0] * n
    def dfs_b(u, p):
        total = values[u] % k
        for v in g[u]:
            if v != p:
                dfs_b(v, u)
                total = (total + prefix_[v]) % k
        prefix_[u] = total
    dfs_b(0, -1)
    print(*prefix_)
    cnt = sum(1 if prefix_[i] == 0 else 0 for i in range(1, n))
    print(cnt+1)
    
    
if __name__ == "__main__":
    main()