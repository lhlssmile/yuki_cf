from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def solve():
    n = int(input())
    a = list(map(int, input().split()))
    
    def cost2(x, y):
        # 使两个元素相等的最小代价
        return abs(x - y)
    
    def cost3(x, y, z):
        # 使三个元素相等的最小代价（使用中位数）
        vals = sorted([x, y, z])
        median = vals[1]
        return abs(vals[0] - median) + abs(vals[2] - median)
    
    def solve_linear(arr):
        # 解决线性数组的DP
        m = len(arr)
        
        dp = [float('inf')] * (m + 1)
        dp[0] = 0
        
        for i in range(2, m + 1):
            # 尝试长度为2的块
            dp[i] = min(dp[i], dp[i-2] + cost2(arr[i-2], arr[i-1]))
            
            # 尝试长度为3的块
            if i >= 3:
                dp[i] = min(dp[i], dp[i-3] + cost3(arr[i-3], arr[i-2], arr[i-1]))
        
        return dp[m]
    
    ans = float('inf')
    
    # 尝试3个可能的断点
    for cut in range(3):
        if cut >= n:
            continue
        
        # 重新排列数组：从cut位置开始
        reordered = []
        for i in range(n):
            reordered.append(a[(cut + i) % n])
        
        # 计算线性数组的最优解
        result = solve_linear(reordered)
        ans = min(ans, result)
    
    print(ans)

t = II()
for _ in range(t):
    solve()