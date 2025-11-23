from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
'''
找到子数组满足:
    1. 子数组XOR为0
    2. 子数组中偶数 奇数 数量相等

    a = 3 1 3 2 0 -> dp?
'''
def main():
    a = LII()
    n = len(a)
    seen = {}
    seen[(0, 0)] = -1
    prefix_xor = diff = 0
    ans = 0

    for i in range(n):
        prefix_xor ^= a[i]
        diff += 1 if a[i] & 1 else -1

        k = (prefix_xor, diff)
        if k in seen:
            ans = max(ans, i - seen[k])
        else:
            seen[k] = i
    return ans
if __name__ == "__main__":
    ans = main()
    print(ans)
    