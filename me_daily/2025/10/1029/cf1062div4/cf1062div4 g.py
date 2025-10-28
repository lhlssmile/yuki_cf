from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

t = II()
for _ in range(t):
    n = II()
    a = LII()
    c = LII()
    
    # 计算前缀和，用于快速计算区间和
    prefix_c = [0] * (n + 1)
    for i in range(n):
        prefix_c[i + 1] = prefix_c[i] + c[i]
    
    # DP解法：dp[i] = 保留位置i时的最小代价
    INF = float('inf')
    dp = [INF] * n
    
    # 初始化：第0个位置
    dp[0] = 0
    
    for i in range(1, n):
        # 选择1：修改前面所有位置，保留位置i
        dp[i] = prefix_c[i]
        
        # 选择2：从之前某个位置j转移到位置i
        for j in range(i):
            if a[j] <= a[i]:  # 可以从位置j转移到位置i
                # 代价 = dp[j] + 修改(j+1到i-1)的代价
                cost = dp[j] + (prefix_c[i] - prefix_c[j + 1])
                dp[i] = min(dp[i], cost)
    
    # 答案是保留某个位置i，然后修改i+1到n-1的最小代价
    result = prefix_c[n]  # 修改所有位置
    for i in range(n):
        # 保留位置i，修改i+1到n-1
        cost = dp[i] + (prefix_c[n] - prefix_c[i + 1])
        result = min(result, cost)
    
    print(result)