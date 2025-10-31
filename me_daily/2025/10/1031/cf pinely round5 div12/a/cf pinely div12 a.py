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
    r0, x, d, n = LII()
    rounds = SI()  # 读取字符串而不是整数列表
    
    current_rating = r0
    ans = 0
    
    for i in range(n):
        if rounds[i] == '1':  # div1
            ans += 1
            # 如果后面还有div2，尽量降低rating为后续做准备
            if i < n - 1 and '2' in rounds[i+1:]:
                current_rating = max(0, current_rating - d)
        else:  # div2
            if current_rating < x:
                ans += 1
                # 如果后面还有div2，继续保持低rating
                if i < n - 1 and '2' in rounds[i+1:]:
                    current_rating = max(0, current_rating - d)
    
    print(ans)