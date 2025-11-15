from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


def count_pairs_sum_ge(A: int, B: int, T: int) -> int:
    # Count pairs (a,b) with 0<=a<=A, 0<=b<=B, a+b >= T
    total = (A + 1) * (B + 1)
    if T <= 0:
        return total
    S = T - 1
    # Count pairs with sum <= S
    a, b = A, B
    if a > b:
        a, b = b, a
    if S < 0:
        le = 0
    elif S <= a:
        le = (S + 1) * (S + 2) // 2
    elif S <= b:
        le = (a + 1) * (S + 1) - a * (a + 1) // 2
    else:
        p = min(a, S - b)
        u = min(a, S)
        m = u - p
        # (p+1) rows fully saturated to B+1, then m rows with decreasing caps
        le = (p + 1) * (b + 1) + m * (S - p + 1) - m * (m + 1) // 2
    return total - le


def solve():
    s = SI()
    n = len(s)
    # positions of zeros
    pos = [i for i, ch in enumerate(s) if ch == '0']
    M = len(pos)
    # all-ones substrings
    if M == 0:
        print(n * (n + 1) // 2)
        return
    # build ones runs between zeros: g[0] before first zero, g[1] between zero0 and zero1, ..., g[M] after last zero
    g = [0] * (M + 1)
    g[0] = pos[0]
    for i in range(M - 1):
        g[i + 1] = pos[i + 1] - pos[i] - 1
    g[M] = n - 1 - pos[M - 1]

    # prefix sums of g (P[k] = sum g[0..k-1])
    P = [0]
    for val in g:
        P.append(P[-1] + val)

    # count substrings with zero zeros (pure ones runs)
    ans = 0
    for r in g:
        ans += r * (r + 1) // 2

    # enumerate z = number of zeros in substring, only up to sqrt(n)
    B = int(n ** 0.5) + 1
    max_z = min(M, B)
    for z in range(1, max_z + 1):
        # choose a block of z consecutive zeros: indices i..i+z-1 among pos
        for i in range(0, M - z + 1):
            L = g[i]
            R = g[i + z]
            # ones fully inside the block = sum of g[i+1 .. i+z-1]
            mid = P[i + z] - P[i + 1]
            need = z * z - mid
            ans += count_pairs_sum_ge(L, R, need)

    print(ans)


if __name__ == "__main__":
    solve()