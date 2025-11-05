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
    t = II()
    for _ in range(t):
        n, q = LII()
        a = [0] + LII()
        
        # 前缀和数组：0 的个数、1 的个数、相邻不同的次数（diff）
        sum0 = [0] * (n + 1)
        sum1 = [0] * (n + 1)
        diff = [0] * (n + 1)
        
        for i in range(1, n + 1):
            sum0[i] = sum0[i - 1] + (a[i] == 0)
            sum1[i] = sum1[i - 1] + (a[i] == 1)
            # 相邻不同则 diff +1
            d = 1 if a[i] != a[i - 1] else 0
            diff[i] = diff[i - 1] + d
        
        # 处理每个查询
        for __ in range(q):
            l, r = LII()
            cnt0 = sum0[r] - sum0[l - 1]
            cnt1 = sum1[r] - sum1[l - 1]
            
            # 如果 0 或 1 的个数不是 3 的倍数，无法完全删除
            if cnt0 % 3 != 0 or cnt1 % 3 != 0:
                print(-1)
                continue
            
            # 基础答案是 cnt0//3 + cnt1//3
            ans = cnt0 // 3 + cnt1 // 3
            
            # 如果整个区间相邻全不同（即 diff[r] - diff[l] == r - l）
            # 那么需要额外 +1 次操作（因为无法局部合并，必须跨段）
            num_pairs = r - l
            switches = diff[r] - diff[l]
            if num_pairs == switches:
                ans += 1
            
            print(ans)

solve()
    