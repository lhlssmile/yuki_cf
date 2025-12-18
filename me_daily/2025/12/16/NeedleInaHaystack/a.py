from collections import Counter
import sys

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
SI = lambda: input()

tt = II()
for _ in range(tt):
    s = SI()
    t_str = SI()  # t 关键词，改 t_str
    s_cnt = Counter(s)
    t_cnt = Counter(t_str)
    
    # 检查够
    possible = True
    for c in s_cnt:
        if t_cnt[c] < s_cnt[c]:
            possible = False
            break
    if not possible:
        print("Impossible")
        continue
    
    # 建 t'：剩余字母从小到大
    extra = {c: t_cnt[c] - s_cnt.get(c, 0) for c in t_cnt}
    t_prime = ''
    for oc in range(26):
        c = chr(ord('a') + oc)
        t_prime += c * extra.get(c, 0)
    
    # merge 贪心
    res = []
    i, j = 0, 0
    ns, nt = len(s), len(t_prime)
    while i < ns or j < nt:
        if i == ns:
            res.append(t_prime[j])
            j += 1
        elif j == nt:
            res.append(s[i])
            i += 1
        else:
            if s[i] < t_prime[j]:
                res.append(s[i])
                i += 1
            elif t_prime[j] < s[i]:
                res.append(t_prime[j])
                j += 1
            else:  # s[i] == t_prime[j]
                res.append(s[i])  # 优先 s
                i += 1
    print(''.join(res))