from collections import defaultdict
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
    n, k = LII()
    a = [0] + LII()  # 哨兵 a[0]=0
    def check(v):
        sum_ = [0] * (n + 1) 
        for i in range(1, n + 1):
            sum_[i] = 1 if a[i] >= v else -1
            sum_[i] += sum_[i - 1]
        pos = 0
        for i in range(k, n + 1):
            if sum_[i - k] < sum_[pos]:
                pos = i - k
            if sum_[i] - sum_[pos] >= 0:
                return [pos + 1, i]
        return [0, 0]
    
    lo, hi = 1, n
    ans = 0 
    res = [0, 0]  
    while lo <= hi:
        vi = lo + (hi - lo) // 2
        pr = check(vi) 
        if pr[0] > 0:  # 可行，记录并找更大
            ans = vi
            res = pr
            lo = vi + 1
        else:
            hi = vi - 1
    print(ans, res[0], res[1])