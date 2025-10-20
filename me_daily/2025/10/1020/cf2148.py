import sys

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
out = []

t = II()
for _ in range(t):
    n = II()
    a = LII()
    
    even_sum = sum(x for x in a if x % 2 == 0)
    odds = sorted(x for x in a if x % 2 == 1)
    k = len(odds)
    if k == 0:
        out.append('0')
    else:
        num_ex = k // 2
        sum_ex = sum(odds[:num_ex])
        sum_odds = sum(odds)
        total = even_sum + sum_odds - sum_ex
        out.append(str(total))

sys.stdout.write("\n".join(out) + "\n")


