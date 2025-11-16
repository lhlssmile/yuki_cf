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
MAXX = 10 ** 15
1000000000000000
1 <= n <= 10^15
给你一个 正 整数 n。

对于从 1 到 n 的每个整数 x，我们记下通过移除 x 的十进制表示中的所有零而得到的整数。

返回一个整数，表示记下的 不同 整数的数量。

也可以倒着想 从1开始 1 * 10 ^i? i 从0开始 直到>x停?
1~10 9 1~100 - 10? 1~1000 ? 100 200 ... -100?
'''
x = II()
s = str(x)
ans = 0
L = len(s)

for k in range(1, L):
    ans += 9 ** k

for i, ch in enumerate(s):
    d = int(ch)
    if d == 0:
        break
    ans += (d - 1) * (9 ** (L - i - 1))
else:
    ans += 1

print(ans)