from collections import defaultdict
from typing import List
import sys
from sortedcontainers import SortedList
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



def main(nums, k, x):
    ans = [0] * (len(nums) - k + 1)
    cnt = defaultdict(int)
    sl = 0
    L, R = SortedList(), SortedList()
    def add(v: int) -> None:
        if cnt[v] == 0: return
        p = (cnt[v], v)
        if L and p > L[0]:
            nonlocal sl
            sl += p[0] * p[1]
            L.add(p)
        else:
            R.add(p)
    def remove(v: int) -> None:
        if cnt[v] == 0: return
        p = (cnt[v], v)
        if p in L:
            nonlocal sl
            sl -= p[0] * p[1]
            L.remove(p)
        else:
            R.remove(p)
    def l2r():
        p = L[0]
        nonlocal sl
        sl -= p[0] * p[1]
        L.remove(p)
        R.add(p)
    def r2l():
        p = R[-1]
        nonlocal sl
        sl += p[0] * p[1]
        R.remove(p)
        L.add(p)
    for r, in_ in enumerate(nums):
        remove(in_)
        cnt[in_] += 1
        add(in_)

        l = r + 1 - k
        if l < 0: continue

        while R and len(L) < x:
            r2l()
        while len(L) > x:
            l2r()
        ans[l] = sl

        out = nums[l]
        remove(out)
        cnt[out] -= 1
        add(out)
    return ans
if __name__ == "__main__":
    k, a = LII()
    nums = LII()
    main(nums, k, a)