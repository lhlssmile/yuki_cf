from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

# t =  II()
# for _ in range(t):
#     n = II()
#     prices = LII()
    
#     dec = [1] * n
#     # 找到最长的递减子序列
#     for i in range(1,n):
#         if prices[i] + 1 == prices[i-1]:
#             dec[i] = dec[i-1]+1    
#     print(sum(dec))


def main():
    ans,cur = 0,0
    # n = II()
    a = LII()
    n = len(a)
    for i in range(n):
        if i > 0 and a[i] == a[i-1] - 1:
            cur += 1
        else:
            cur = 1
        ans += cur
    return ans

if __name__ == "__main__":
    print(main())
