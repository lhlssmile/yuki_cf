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
x次操作 移除y * i的数/? 这个y是索引? 最后找到第k个数若是ra小于k那么返回-1
1 2 3 4 5 ...... 10 ** 12
逻辑删除可行吗?还是直接有公式

'''
t = II()
N = 10 ** 12
for _ in range(t):
    x, y, k = LII()
    # y == 1直接全删了
    if y == 1:
        print(-1)
        continue
    idx = k
    # 反向映射 x 次：一轮的旧索引 i = k + floor((k-1)/(y-1))
    for _ in range(x):  
        if idx > N:
            break
        idx += (idx - 1) // (y - 1)
    print(idx if idx <= N else -1)

    
