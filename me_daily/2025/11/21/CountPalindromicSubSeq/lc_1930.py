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

ans = 0

# 枚举最左最右的字符

for a in ascii_lowercase:
    i = s.find(a)
    if i < 0:
        continue
    j = s.rfind(a)
    ans += len(set(s[i + 1:j]))
print(ans)

# 枚举中间的 si

suf_cnt = Counter(s[1:])
pre_set = set()
st = set()

for i in range(1, len(s) - 1):
    mid = s[i]
    suf_cnt[mid] -= 1
    if suf_cnt[mid] == 0:
        del suf_cnt[mid]
    pre_set.add(s[i - 1])
    for a in pre_set & suf_cnt.keys():
        st.add(a + mid)
print(len(st))


# 位运算

n = len(s)

ord_a = ord('a')

suf_Cnt = [0] * 26
suf = 0

for ch in s[1:]:
    ch = ord(ch) - ord_a
    suf_Cnt[ch] += 1
    suf |= 1 << ch
pre = 0
ans = [0] * 26

for i in range(1, n -1 ) :
    mid = ord(s[i]) - ord_a
    suf_Cnt[mid] -= 1
    if suf_Cnt[mid] == 0:
        suf_Cnt ^= 1 << mid
    pre |= 1  << (ord(s[i - 1]) - ord_a)
    ans[mid] |= pre & suf

print(sum(mask.bit_count() for mask in ans))