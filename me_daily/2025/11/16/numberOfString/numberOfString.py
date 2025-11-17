
from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


s = SI()
n = len(s)
a = [i for i in range(n) if s[i] == '0']
total1 = n - len(a)
a.append(n)

'''
si (cnt0 * cnt0 <= cnt1)
'''

cnt_pass0 = 0
ans = 0

for l, c in enumerate(s):
    if c == '1':
        ans += a[cnt_pass0] - l
    for k in range(cnt_pass0, len(a) - 1):
        cnt0 =  k - cnt_pass0 + 1
        
        if cnt0 * cnt0 > total1:
            break
        cnt1 = a[k] - l + 1 - cnt0
        if cnt0 * cnt0 <= cnt1:
            ans += a[k + 1] - a[k]
        else:
            ans += max(a[k + 1] - a[k] - max(cnt0 * cnt0 - cnt1, 0), 0)

    if c == '0':
        cnt_pass0 += 1


print(ans)
