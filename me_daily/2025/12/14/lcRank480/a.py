from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


k = II()
nums = LII()


nums = sorted(nums)
diff = 0
n = len(nums)
for i in range(k):
    diff += (nums[n-1-i] - nums[i])
print(diff)