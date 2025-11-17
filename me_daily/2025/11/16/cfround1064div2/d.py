from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


MOD = 998244353

t = II()
for _ in range(t):
    n = II()
    a = [0] + LII()
    cnt = Counter(a[1:])
    cs = sorted(cnt.values(), reverse=True)
    if not cs:
        print(0)
        continue
    total = 1
    for c in cs:
        total = (total * (c + 1)) % MOD
    total = (total - 1) % MOD
    M = cs[0]
    cc = Counter([c for c in cs if c < M])
    if not cc:
        print(total)
        continue
    max_f = max(cc.values())
    fac = [1] * (max_f + 1)
    for i in range(1, max_f + 1):
        fac[i] = fac[i - 1] * i % MOD
    invfac = [1] * (max_f + 1)
    invfac[max_f] = pow(fac[max_f], MOD - 2, MOD)
    for i in range(max_f, 0, -1):
        invfac[i - 1] = invfac[i] * i % MOD
    dp = [0] * M
    dp[0] = 1
    for w, f in cc.items():
        new = dp[:]
        up = min(f, (M - 1) // w)
        for t_choose in range(1, up + 1):
            coef = fac[f] * invfac[t_choose] % MOD
            coef = coef * invfac[f - t_choose] % MOD
            coef = coef * pow(w, t_choose, MOD) % MOD
            step = w * t_choose
            for s in range(0, M - step):
                new[s + step] = (new[s + step] + dp[s] * coef) % MOD
        dp = new
    bad = 0
    for s in range(1, M):
        bad = (bad + dp[s]) % MOD
    ans = (total - bad) % MOD
    print(ans)

    