from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()




# 让numsi 都变成回文数的最小操作次数. -> 怎么找到离得最近的回文数? 不能去高位1?/不能改位数 
# 改后边的代价小.


n = II()
nums = LII()

def is_binary_palindrome(num):
    s = bin(num)[2:]
    return s == s[::-1]

ans = []

for x in nums:
    if is_binary_palindrome(x):
        ans.append(0)
        continue
    dist = 1
    while True:
        down = x - dist
        up = x + dist
        if down >= 1 and is_binary_palindrome(down):
            ans.append(dist)
            break
        if is_binary_palindrome(up):
            ans.append(dist)
            break
        dist += 1

print(*ans)