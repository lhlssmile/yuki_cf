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
    balance = LII()
    # 环形数组 转账给左右邻居 返回所有非负
    n = len(balance)


    if sum(balance) < 0: return -1
    bk,k = 0,0
    for i, x in enumerate(balance):
        if x < 0: 
            bk = -x
            k = i
            break

    dist_bucket = defaultdict(int) # key:dist,value:sum(balance)
    for i in range(n):
        # dist = abs(k - i) i ~(0,n-1)
        # value: sum(balancei)
        if i == k:continue
        diff = abs(i - k)
        dist = min(diff, n - diff)
        dist_bucket[dist] += balance[i]
    
    moves = 0
    remaining = bk
    for dist in sorted(dist_bucket.keys()):
        if remaining <= 0:break
        avail = dist_bucket[dist]
        take = min(remaining, avail)
        moves += take * dist
        remaining -= take
    if remaining > 0:return -1
    return moves


if __name__ == "__main__":
    print(main())